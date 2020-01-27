#include "utils.h"
#include "constants.h"

namespace utils {

TexturePack::TexturePack(const QString path)
    : left_block(kTexturesPath + path + "/left.png"),
      middle_block(kTexturesPath + path + "/middle.png"),
      right_block(kTexturesPath + path + "/right.png") {}

}
