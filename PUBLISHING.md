# Publishing

How a release of `Aspose.Slides.Cpp.FOSS` reaches nuget.org, what stops it, and what to do when
something goes wrong halfway.

There is **no API key in this repository**, and there is not meant to be. The publish job proves its
identity to nuget.org with a GitHub OIDC token and receives a key valid for one hour. Nothing
long-lived exists to leak, rotate, or forget to revoke.

> **The package must be author-signed, and signing happens outside this repository.** nuget.org
> refuses an unsigned package under this owner — `400 — This package must be signed with a
> registered certificate` — and every Aspose package, commercial and open-source alike, is
> author-signed with `CN=ASPOSE PTY LTD`. The certificate is not here and must not be: it lives in
> the certificate store of an internal build agent, and a separate job there applies it.
>
> So the package this repository *builds* is not the package it *pushes*. The signed one comes back
> and is attached to the release, and the workflow proves it is the built package plus a signature
> and nothing else before pushing it. Step 5 below is where that happens.

## Before the first release: two things this repository cannot do for itself

Neither is code, and neither can be done from here.

| Missing | Who | What happens without it |
|---|---|---|
| A **trusted-publishing policy** on nuget.org for `Aspose.Slides.Cpp.FOSS`, bound to this repository, the workflow file `nuget-release.yml` and the environment `nuget.org` | a member of the `Aspose` organisation on nuget.org | The OIDC exchange fails. The error names the token, not the missing policy. |
| The **`NUGET_USER`** environment secret on the `nuget.org` environment, holding the nuget.org *profile name* — not an email address, which fails the exchange | a repository admin | `NuGet/login` receives an empty user and the exchange fails. |

The `nuget.org` environment itself already exists here, with `yury-knml` as required reviewer and a
deployment policy admitting only `v*` tags. It holds no secret yet.

## Cutting a release

1. **Make the release commit.** Set the version in `CMakeLists.txt` — `project(AsposeSlidesFoss
   VERSION ...)` is the only place a version is written — and fix everything the release makes
   untrue. The checklist is below.
2. **Push it to `main` and let CI go green**, including the `package` job, which builds all four
   MSVC configurations, asserts on the `.nupkg` and consumes it from a real Visual Studio project.
3. **Dry-run the release workflow.** Actions → *Release to NuGet* → *Run workflow*. It runs every
   guard and the whole of CI, and stops short of publishing. It reports the tag a release would need.
4. **Push the tag.** `git tag v26.9.0 && git push origin v26.9.0`. The tag must be `v` followed by
   exactly the version in `CMakeLists.txt`; the workflow refuses anything else. The guards run, CI
   builds and verifies the package, and the publish job then **waits for approval**.
5. **Sign it, while the job waits.** That pause is the signing window, and it exists for this.
   1. Download `Aspose.Slides.Cpp.FOSS.<version>.nupkg` from the run's artefacts — the built file,
      never a rebuild.
   2. Run the internal signing job with it. It signs and verifies, and publishes nothing.
   3. Download the signed package from that job.
   4. Create a **draft release** for the tag and attach the signed `.nupkg` to it.
6. **Approve the deployment.** The publish job takes the signed package from the release, proves it
   is byte-identical to the one CI built apart from the added signature, and pushes it. Until you
   approve, nothing has been sent.
7. **Watch it land.** The workflow polls nuget.org until the version is actually downloadable, then
   publishes the release with notes from the changelog section for that version.

### The release-commit checklist

Editing the version is one step of cutting a release and not the whole of it. These files state, in
the present tense, things that stop being true the moment the package exists:

| File | What changes |
|---|---|
| `CMakeLists.txt` | `project(... VERSION ...)`. Everything else reads it from there. |
| `CHANGELOG.md` | Rename `## [Unreleased]` to `## [<version>]`, and add the matching link-reference at the foot. **The release notes are that section**, so it is the release page's text. |
| `README.md` | The **Installing from NuGet** section, if what the package carries has changed. |
| `SECURITY.md` | **Supported versions**: the table and the paragraph above it currently rest on nothing having been released, and on there being no tag. Both stop being true at the first release. |
| `docs/nuget/README.md` | The package page — the file consumers read first. Check it says what this version does. |
| `packaging/vcpkg/vcpkg.json`, `packaging/conan/conandata.yml` | Both name a version and a tag. They are drafts and are not submitted, but a draft that names last release's tag is worse than one that names none. |

Do not date the changelog heading in advance. The release commit lands before the tag, and the tag
is pushed by a person; a date written ahead of time asserts a publication that has not happened.

## What the workflow checks, in order

Everything before the push is designed to fail on a branch, in a dry run, or in the guard job —
somewhere cheap — rather than after a version number has been spent.

| # | Guard | Why it exists |
|---|---|---|
| 1 | The version comes from `pack.py --print-version`, which reads `CMakeLists.txt` | One implementation of "what version is this?" instead of two that can disagree. An empty result stops the release. |
| 2 | The tag equals `v<version>`, and the version is a plain three-part release | A version is published once and can never be replaced. A tag that disagrees with the package is a mislabelled release nobody can correct afterwards. |
| 3 | `CHANGELOG.md` has a section for this version | The release notes come from it. A release whose notes came out empty is not noticed until someone reads the page, by which time the package is public. |
| 4 | Nothing key-shaped is committed in the tracked tree | This repository holds no publishing credential by design. The day this fires, something has changed. |
| 5 | nuget.org is asked whether the version already exists | Three outcomes, and the third is the point: an unexpected status **stops** the release. Treating "I could not tell" as "not published" is how a version gets pushed over one that exists. |
| 6 | The full CI suite runs at the released commit, as a reusable workflow | Seven platform legs, the sanitizer, the CMake floor, and the package job. The artefact pushed is the one those jobs built and inspected, not a rebuild nothing tested. |
| 7 | `check_package.py` passes, with the version cross-checked against the tag | It asserts the `.targets` is at the one path NuGet imports, that all four platform/configuration pairs carry all three archives, and that pugixml's headers are present. |
| 8 | The signed package differs from the built one by exactly one added entry, `.signature.p7s`, and nothing else | Signing happens on another machine, so this hand-off is the one place a substituted artefact could enter. |
| 9 | After the push, nuget.org must actually serve the version | A successful push is not a published package. |

## Verifying by hand

A green tick is not evidence. These are:

```bash
ID=aspose.slides.cpp.foss
VER=26.9.0

curl -s "https://api.nuget.org/v3-flatcontainer/$ID/index.json" | grep "$VER"
curl -s -o /dev/null -w '%{http_code}\n' \
  "https://api.nuget.org/v3-flatcontainer/$ID/$VER/$ID.$VER.nupkg"

# Owners and the verified-prefix flag live ONLY on the search resource. Search has two replicas,
# and they disagree while indexing settles, so check both and re-check before believing either.
curl -s "https://azuresearch-usnc.nuget.org/query?q=packageid:Aspose.Slides.Cpp.FOSS&prerelease=true"
curl -s "https://azuresearch-ussc.nuget.org/query?q=packageid:Aspose.Slides.Cpp.FOSS&prerelease=true"
```

And on a machine that has never seen the package — which is the only check that exercises the thing
most likely to be wrong, NuGet finding the `.targets` inside the package:

```powershell
msbuild examples\nuget-consumer\nuget-consumer.vcxproj -t:restore,build ^
    -p:Configuration=Release -p:Platform=x64 -p:AsposeSlidesFossVersion=26.9.0
```

Finally, open the package page and look at it. The icon, the README, the badges and the banner
either render or they do not, and nuget.org reports a readme it could not render **only to the
package owners** — no HTTP status anywhere says so.

## Re-running a release that failed halfway

**Re-running the same tag is safe, and is the right move.** Guard 5 asks nuget.org whether the
version already exists; if it does, the push is skipped and only the verification and the GitHub
release run. Do not invent a new version number to get around a failed run — that spends a version
to work around a problem that may not be in the package at all.

- **Before the push** — any guard, CI, the package assertions. Nothing was sent. Fix and re-push the
  tag.
- **The wait step timed out.** This does **not** mean the push failed. nuget.org validates and
  indexes after accepting a package, and the workflow gives that about 28 minutes. Look at the
  package page: validation failures appear there and are emailed to the package owners.
- **The GitHub release step failed.** The package is published; only the release page is missing.
  Re-run the tag — the step is idempotent.

### What is not yet known, and is not guessed here

Three behaviours this document would like to state are **undocumented by nuget.org**, and no answer
is written here rather than an inferred one:

1. What the flat container returns for a version that has been pushed but is still validating.
2. What a second push of the same version returns during that window.
3. Whether a version that **fails** validation can ever be re-pushed, or whether the number is spent.

The way to answer them is a rehearsal against `https://int.nugettest.org`. **That rehearsal has not
been run**, for this package or for the .NET one.

## Publication history

| Version | Date | Notes |
|---|---|---|
| — | — | Nothing has been published yet. |
