#include "animation.h"
#include "constants.h"
#include <QDebug>

Animation::Animation(const char* img_path, int frame_height, int frame_width)
{
    QPixmap image(img_path);
    for (int x = 0; x + frame_width < image.width(); x += frame_width) {
        QRect rect(x, 0, frame_width, frame_height);
        frames_.insert(frames_.end(), image.copy(rect));
    }
    cur_frame_ = frames_.begin();
}

Animation::Animation(const Animation& lhs)
    : frames_(lhs.frames_),
      cur_frame_(frames_.begin()) {}


void Animation::NextFrame() {
    cur_frame_++;
    if (cur_frame_ == frames_.end()) {
        cur_frame_ = frames_.begin();
    }
}

void Animation::PreviousFrame() {
    if (cur_frame_ == frames_.begin()) {
        cur_frame_ = frames_.end();
    }
    cur_frame_--;
}

QPixmap Animation::CurrentFrame() const {
    return *cur_frame_;
}
