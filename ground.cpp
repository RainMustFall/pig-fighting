#include "ground.h"
#include <QDebug>

TexturePack::TexturePack(const QString path)
    : left_block(":/resources/textures/" + path + "/left.png"),
      middle_block(":/resources/textures/" + path + "/middle.png"),
      right_block(":/resources/textures/" + path + "/right.png") {}

Ground::Ground(int x, int y, int height, int width, TextureType type)
    : GameObject (x, y, height, width),
      texture(width, height)
{
    if (width % height != 0) {
        throw std::invalid_argument("The length of a ground must be divided by the height for correct rendering.");
    }

    std::vector<TexturePack>textures = {{"sand"}, {"grass"}};

    texture.fill(QColor(0, 0, 0, 0));
    TexturePack& cur_texture = textures[static_cast<size_t>(type)];

    QPainter painter(&texture);
    painter.drawPixmap(
            QRectF(0, 0, height, height),
            cur_texture.left_block.scaled(height, height, Qt::KeepAspectRatio, Qt::SmoothTransformation),
            QRectF(0, 0, height, height));

    for (int x = height; x + height < width; x += height) {
        painter.drawPixmap(
                QRectF(x, 0, height, height),
                cur_texture.middle_block.scaled(height, height, Qt::KeepAspectRatio, Qt::SmoothTransformation),
                QRectF(0, 0, height, height));
    }

    painter.drawPixmap(
            QRectF(width - height, 0, height, height),
            cur_texture.right_block.scaled(height, height, Qt::KeepAspectRatio, Qt::SmoothTransformation),
            QRectF(0, 0, height, height));
}

void Ground::Draw(QPainter& painter) const {
    painter.drawPixmap(position_.x, position_.y,
                       bBox_.width_, bBox_.height_,
                       texture);
}
