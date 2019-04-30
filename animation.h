#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
#include <vector>
#include <QPixmap>

const std::vector<QPixmap>ControlVec;

class Animation
{
public:
    Animation(const char* img_path, int frame_height, int frame_width);

    void NextFrame();
    void PreviousFrame();
    QPixmap CurrentFrame() const;
//private:
    std::vector<QPixmap>frames_;
    std::vector<QPixmap>::iterator cur_frame_;
};

#endif // ANIMATION_H
