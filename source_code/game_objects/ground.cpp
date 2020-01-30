#include "./ground.h"

#include <QDebug>

#include <vector>

Ground::Ground(int x, int y, int height, int width, utils::TextureType type)
    : GameObject(x, y, height, width), texture_(width, height) {
  if (width % height != 0) {
    throw std::invalid_argument(
        "The length of a ground must be divided by the height for correct "
        "rendering.");
  }

  std::vector<utils::TexturePack> textures = {
      utils::TexturePack("grass"),
      utils::TexturePack("sand"),
      utils::TexturePack("cave"),
      utils::TexturePack("snow")
  };

  texture_.fill(QColor(0, 0, 0, 0));
  utils::TexturePack& cur_texture = textures[static_cast<size_t>(type)];

  QPainter painter(&texture_);
  painter.drawPixmap(
      QRectF(0, 0, height, height),
      cur_texture.left_block.scaled(height, height, Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation),
      QRectF(0, 0, height, height));

  for (int x = height; x + height < width; x += height) {
    painter.drawPixmap(
        QRectF(x, 0, height, height),
        cur_texture.middle_block.scaled(height, height, Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation),
        QRectF(0, 0, height, height));
  }

  painter.drawPixmap(
      QRectF(width - height, 0, height, height),
      cur_texture.right_block.scaled(height, height, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation),
      QRectF(0, 0, height, height));
}

void Ground::Draw(QPainter* painter) const {
  painter->drawPixmap(xPos(), yPos(), bBox_.width_, bBox_.height_, texture_);
}
