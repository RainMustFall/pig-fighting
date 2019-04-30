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
    Animation(const Animation& lhs);

    void NextFrame();
    void PreviousFrame();
    QPixmap CurrentFrame() const;
//private:
    std::list<QPixmap>frames_;
    std::list<QPixmap>::iterator cur_frame_;
};

#endif // ANIMATION_H
