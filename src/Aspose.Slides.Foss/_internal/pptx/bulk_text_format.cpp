// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/_internal/pptx/bulk_text_format.h>

#include <stdexcept>
#include <string>

namespace Aspose::Slides::Foss::Internal::pptx {

// ── Element tag constants ───────────────────────────────────────────────

static const std::string kTxBody = "a:txBody";
static const std::string kP = "a:p";
static const std::string kR = "a:r";
static const std::string kRPr = "a:rPr";
static const std::string kEndParaRPr = "a:endParaRPr";
static const std::string kPPr = "a:pPr";
static const std::string kBodyPr = "a:bodyPr";
static const std::string kTcPr = "a:tcPr";

// ── Low-level XML helpers ───────────────────────────────────────────────

void copy_xml_attrs(pugi::xml_node src, pugi::xml_node dst) {
    for (auto attr : src.attributes()) {
        dst.attribute(attr.name())
            ? dst.attribute(attr.name()).set_value(attr.value())
            : dst.append_attribute(attr.name()).set_value(attr.value());
    }
}

void replace_or_add_child(pugi::xml_node parent, pugi::xml_node src_child) {
    auto existing = parent.child(src_child.name());
    if (existing) {
        // Replace: remove existing, then insert a copy at the same position.
        parent.remove_child(existing);
    }
    parent.append_copy(src_child);
}

void apply_rpr_to_element(pugi::xml_node src_rpr, pugi::xml_node target) {
    copy_xml_attrs(src_rpr, target);
    for (auto child : src_rpr.children()) {
        replace_or_add_child(target, child);
    }
}

// ── Per-format appliers ─────────────────────────────────────────────────

void apply_portion_format(std::span<pugi::xml_node> tc_nodes,
                          pugi::xml_node src_rpr) {
    if (!src_rpr) {
        return;
    }
    for (auto tc : tc_nodes) {
        auto txbody = tc.child(kTxBody.c_str());
        if (!txbody) {
            continue;
        }
        for (auto p : txbody.children(kP.c_str())) {
            // Apply to runs (<a:r>).
            for (auto r : p.children(kR.c_str())) {
                auto rpr = r.child(kRPr.c_str());
                if (!rpr) {
                    rpr = r.prepend_child(kRPr.c_str());
                }
                apply_rpr_to_element(src_rpr, rpr);
            }
            // Apply to endParaRPr.
            auto end_rpr = p.child(kEndParaRPr.c_str());
            if (end_rpr) {
                apply_rpr_to_element(src_rpr, end_rpr);
            }
        }
    }
}

void apply_paragraph_format(std::span<pugi::xml_node> tc_nodes,
                            pugi::xml_node src_ppr) {
    if (!src_ppr) {
        return;
    }
    for (auto tc : tc_nodes) {
        auto txbody = tc.child(kTxBody.c_str());
        if (!txbody) {
            continue;
        }
        for (auto p : txbody.children(kP.c_str())) {
            auto ppr = p.child(kPPr.c_str());
            if (!ppr) {
                ppr = p.prepend_child(kPPr.c_str());
            }
            copy_xml_attrs(src_ppr, ppr);
            for (auto child : src_ppr.children()) {
                replace_or_add_child(ppr, child);
            }
        }
    }
}

void apply_text_frame_format(std::span<pugi::xml_node> tc_nodes,
                             pugi::xml_node src_txbody) {
    if (!src_txbody) {
        return;
    }
    auto src_body_pr = src_txbody.child(kBodyPr.c_str());
    if (!src_body_pr) {
        return;
    }
    auto vert_attr = src_body_pr.attribute("vert");

    for (auto tc : tc_nodes) {
        auto txbody = tc.child(kTxBody.c_str());
        if (!txbody) {
            continue;
        }
        auto body_pr = txbody.child(kBodyPr.c_str());
        if (!body_pr) {
            body_pr = txbody.prepend_child(kBodyPr.c_str());
        }
        copy_xml_attrs(src_body_pr, body_pr);
        for (auto child : src_body_pr.children()) {
            replace_or_add_child(body_pr, child);
        }
        // Mirror vert on <a:tcPr>.
        if (vert_attr) {
            auto tc_pr = tc.child(kTcPr.c_str());
            if (tc_pr) {
                if (auto existing = tc_pr.attribute("vert")) {
                    existing.set_value(vert_attr.value());
                } else {
                    tc_pr.append_attribute("vert").set_value(vert_attr.value());
                }
            }
        }
    }
}

// ── Variant-based dispatch ──────────────────────────────────────────────

void apply_text_format(std::span<pugi::xml_node> tc_nodes,
                       const TextFormatSource& source,
                       std::function<void()> save_callback) {
    std::visit([&](auto&& s) {
        using T = std::decay_t<decltype(s)>;
        if constexpr (std::is_same_v<T, PortionFormatSource>) {
            apply_portion_format(tc_nodes, s.rpr);
        } else if constexpr (std::is_same_v<T, ParagraphFormatSource>) {
            apply_paragraph_format(tc_nodes, s.ppr);
        } else if constexpr (std::is_same_v<T, TextFrameFormatSource>) {
            apply_text_frame_format(tc_nodes, s.txbody);
        }
    }, source);

    if (save_callback) {
        save_callback();
    }
}

} // namespace Aspose::Slides::Foss::Internal::pptx
