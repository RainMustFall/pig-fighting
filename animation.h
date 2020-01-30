#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
#include <vector>
#include <QPixmap>

class Animation
{
public:
    Animation(const QString& img_path, int frame_height, int frame_width, int dst_height, int dst_width);
    Animation(const Animation& lhs);

    void NextFrame();
    void PreviousFrame();
    void GoToFirstFrame();
    bool IsOnFirstFrame() const;
    QPixmap CurrentFrame() const;
    Animation returnReflectedCopy() const;

private:
    std::list<QPixmap>frames_;
    std::list<QPixmap>::iterator cur_frame_;
};

Animation Reflect(const Animation& animation);

#endif // ANIMATION_H
