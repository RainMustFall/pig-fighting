#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H
#include "game_object.h"
#include "ground.h"

class MovingObject : public GameObject {
public:
    MovingObject(int x, int y, int width, int height);

    void UpdatePosition();
    virtual void ApplyPhysics();

    utils::HitType CheckHitType(const Ground& ground);
    void StabilizePosition(const Ground& ground);

    // It checks whether the object touches the land and, if so,
    // stabilizes its position. If it also touches the top, it
    // returns a pointer to the platform, otherwise nullptr
    const Ground* HitsGround(const std::vector<Ground>& ground);
    void CheckBoundaries();
    void UpdatePlatform(const std::vector<Ground>& ground);

    double GetMoveVectorX() const;
    double GetMoveVectorY() const;

    void AccelerateX(double delta);

protected:
    utils::Point move_vector_ = {0, 0};
    utils::HitType last_hit_;
    utils::Side current_side_ = utils::Side::LEFT;

    // The point is that we temporarily ignore some platform
    // and do not take into account collisions with it.
    // For example, if we want to fall through it
    // down or jump through it from below.
    const Ground* ignored_platform_ = nullptr;
    const Ground* current_platform_ = nullptr;
};

#endif // MOVEOBJECT_H
