// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#include <Aspose/Slides/Foss/picture_frame_lock.h>

#include <cstring>

namespace Aspose::Slides::Foss {

void PictureFrameLock::init_internal(pugi::xml_node pic_locks_element,
                                     Internal::pptx::SlidePart* slide_part) {
    pic_locks_ = pic_locks_element;
    slide_part_ = slide_part;
    xml_backed_ = true;
}

bool PictureFrameLock::get_lock(const char* attr_name, bool fallback) const {
    if (!xml_backed_) return fallback;
    if (pic_locks_.empty()) return false;
    const char* val = pic_locks_.attribute(attr_name).value();
    return std::strcmp(val, "1") == 0;
}

void PictureFrameLock::set_lock(const char* attr_name, bool value, bool& fallback) {
    if (!xml_backed_) {
        fallback = value;
        return;
    }
    if (pic_locks_.empty()) return;
    if (value) {
        if (pic_locks_.attribute(attr_name))
            pic_locks_.attribute(attr_name).set_value("1");
        else
            pic_locks_.append_attribute(attr_name).set_value("1");
    } else {
        pic_locks_.remove_attribute(attr_name);
    }
}

// --- Lock property implementations ---

bool PictureFrameLock::grouping_locked() const { return get_lock("noGrp", grouping_locked_); }
void PictureFrameLock::set_grouping_locked(bool v) { set_lock("noGrp", v, grouping_locked_); }

bool PictureFrameLock::select_locked() const { return get_lock("noSelect", select_locked_); }
void PictureFrameLock::set_select_locked(bool v) { set_lock("noSelect", v, select_locked_); }

bool PictureFrameLock::rotation_locked() const { return get_lock("noRot", rotation_locked_); }
void PictureFrameLock::set_rotation_locked(bool v) { set_lock("noRot", v, rotation_locked_); }

bool PictureFrameLock::aspect_ratio_locked() const { return get_lock("noChangeAspect", aspect_ratio_locked_); }
void PictureFrameLock::set_aspect_ratio_locked(bool v) { set_lock("noChangeAspect", v, aspect_ratio_locked_); }

bool PictureFrameLock::position_locked() const { return get_lock("noMove", position_locked_); }
void PictureFrameLock::set_position_locked(bool v) { set_lock("noMove", v, position_locked_); }

bool PictureFrameLock::size_locked() const { return get_lock("noResize", size_locked_); }
void PictureFrameLock::set_size_locked(bool v) { set_lock("noResize", v, size_locked_); }

bool PictureFrameLock::edit_points_locked() const { return get_lock("noEditPoints", edit_points_locked_); }
void PictureFrameLock::set_edit_points_locked(bool v) { set_lock("noEditPoints", v, edit_points_locked_); }

bool PictureFrameLock::adjust_handles_locked() const { return get_lock("noAdjustHandles", adjust_handles_locked_); }
void PictureFrameLock::set_adjust_handles_locked(bool v) { set_lock("noAdjustHandles", v, adjust_handles_locked_); }

bool PictureFrameLock::arrowheads_locked() const { return get_lock("noChangeArrowheads", arrowheads_locked_); }
void PictureFrameLock::set_arrowheads_locked(bool v) { set_lock("noChangeArrowheads", v, arrowheads_locked_); }

bool PictureFrameLock::shape_type_locked() const { return get_lock("noChangeShapeType", shape_type_locked_); }
void PictureFrameLock::set_shape_type_locked(bool v) { set_lock("noChangeShapeType", v, shape_type_locked_); }

bool PictureFrameLock::crop_locked() const { return get_lock("noCrop", crop_locked_); }
void PictureFrameLock::set_crop_locked(bool v) { set_lock("noCrop", v, crop_locked_); }

bool PictureFrameLock::no_locks() const {
    return !grouping_locked() && !select_locked() && !rotation_locked() &&
           !aspect_ratio_locked() && !position_locked() && !size_locked() &&
           !edit_points_locked() && !adjust_handles_locked() &&
           !arrowheads_locked() && !shape_type_locked() && !crop_locked();
}

} // namespace Aspose::Slides::Foss
