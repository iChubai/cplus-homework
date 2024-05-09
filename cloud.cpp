#include "cloud.h"
#include "config.h"
Cloud::Cloud()
{
    c_cloud.load(CLOUD_PATH);
    c_x = 0;
    c_y = 0;
    c_Free = true;
    c_Speed = CLOUD_SPEED;
}
void Cloud::updatePosition()
{
    if (c_Free)
    {
        return;
    }
    c_x -= c_Speed;
    if (c_x <= -100) {
        c_Free = true;
    }
}