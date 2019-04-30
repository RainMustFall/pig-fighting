#include "animation.h"
#include "constants.h"
#include <QDebug>

Animation::Animation(const char* img_path, int frame_height, int frame_width)
{
    QPixmap image(img_path);
    qDebug() << "Cropping";
    //for (int x = 0; x + frame_width < image.width(); x += frame_width) {
        QRect rect(0, 0, frame_width, frame_height);
        //frames_.insert(frames_.end(), image.copy(rect));
        frames_.push_back(image.copy(rect));
    //}
    cur_frame_ = frames_.begin();
    qDebug() << "Cropped" << frames_.size() << cur_frame_ - frames_.begin()
             << ControlVec.begin() - frames_.begin() << ControlVec.begin() - cur_frame_;
}

void Animation::NextFrame() {
    qDebug() << (cur_frame_ - frames_.begin());
    cur_frame_++;
    if (cur_frame_ == frames_.end()) {
        cur_frame_ = frames_.begin();
    }
    qDebug() << (cur_frame_ - frames_.begin()) << ControlVec.begin() - frames_.begin() << ControlVec.begin() - cur_frame_;;
}

void Animation::PreviousFrame() {
    if (cur_frame_ == frames_.begin()) {
        cur_frame_ = frames_.end();
    }
    cur_frame_--;
}

QPixmap Animation::CurrentFrame() const {
    qDebug() << (cur_frame_ - frames_.begin());
    return *frames_.begin();//cur_frame_;
}
