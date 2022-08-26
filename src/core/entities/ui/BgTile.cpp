#include "BgTile.h"

BgTile::BgTile(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView) {

}
