#include "./animation.h"

#include <QDebug>
#include <QTransform>

#include "./constants.h"

Animation Animation::returnReflectedCopy() const {
  Animation result = *this;
  for (auto& frame : result.frames_) {
    frame = frame.transformed(QTransform().scale(-1, 1));
  }
  return result;
}

Animation::Animation(const QString& img_path, int frame_height, int frame_width,
                     int dst_height, int dst_width) {
  QPixmap image(img_path);
  for (int x = 0; x + frame_width <= image.width(); x += frame_width) {
    QRect rect(x, 0, frame_width, frame_height);
    frames_.insert(frames_.end(), image.copy(rect));
    frames_.back() = frames_.back().scaled(
        dst_height, dst_width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  }
  cur_frame_ = frames_.begin();
}

Animation::Animation(const Animation& lhs)
    : frames_(lhs.frames_), cur_frame_(frames_.begin()) {}

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

bool Animation::IsOnFirstFrame() const { return cur_frame_ == frames_.begin(); }

void Animation::GoToFirstFrame() { cur_frame_ = frames_.begin(); }

QPixmap Animation::CurrentFrame() const { return *cur_frame_; }
