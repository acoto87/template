GameSprite createSprite(GameContext *context, u32 width, u32 height, u8 data[])
{
    GameSprite sprite = (GameSprite){0};
    sprite.frameWidth = width;
    sprite.frameHeight = height;
    sprite.framesCount = 1;

    sprite.image = nvgCreateImageRGBA(context->gfx, width, height, NVG_IMAGE_NEAREST, data);

    sprite.frames[0].dx = 0;
    sprite.frames[0].dy = 0;
    sprite.frames[0].w = width;
    sprite.frames[0].h = height;
    sprite.frames[0].off = 0;
    sprite.frames[0].data = (u8*)xmalloc(width * height * 4);

    if (data)
        memcpy(sprite.frames[0].data, data, width * height * 4);

    return sprite;
}

GameSprite createSpriteFromFrames(GameContext *context, u32 frameWidth, u32 frameHeight, u32 frameCount, GameSpriteFrame frames[])
{
    GameSprite sprite = (GameSprite){0};
    sprite.frameWidth = frameWidth;
    sprite.frameHeight = frameHeight;
    sprite.framesCount = frameCount;

    sprite.image = nvgCreateImageRGBA(context->gfx, frameWidth, frameHeight, NVG_IMAGE_NEAREST, NULL);

    for(s32 i = 0; i < frameCount; i++)
    {
        sprite.frames[i].dx = frames[i].dx;
        sprite.frames[i].dy = frames[i].dy;
        sprite.frames[i].w = frames[i].w;
        sprite.frames[i].h = frames[i].h;
        sprite.frames[i].off = 0;
        sprite.frames[i].data = (u8*)xmalloc(frameWidth * frameHeight * 4);

        if (frames[i].data)
            memcpy(sprite.frames[i].data, frames[i].data, frameWidth * frameHeight * 4);
    }

    return sprite;
}

void updateSpriteImage(GameContext *context, GameSprite sprite, u8 data[])
{
    if (!sprite.image)
    {
        logWarning("Trying to update a sprite with image: %d\n", sprite.image);
        return;
    }

    nvgUpdateImage(context->gfx, sprite.image, data);
}

void renderSubSprite(GameContext *context, GameSprite sprite, rect rs, rect rd, vec2 scale)
{
    if (!sprite.image)
    {
        logWarning("Trying to render a sprite with image: %d\n", sprite.image);
        return;
    }

    nvgRenderSubImage(context->gfx, sprite.image, rs, rd, scale);
}

void renderSprite(GameContext *context, GameSprite sprite, vec2 pos, vec2 scale)
{
    if (!sprite.image)
    {
        logWarning("Trying to render a sprite with image: %d\n", sprite.image);
        return;
    }

    vec2 frameSize = vec2i(sprite.frameWidth, sprite.frameHeight);
    rect rs = rectv(VEC2_ZERO, frameSize);
    rect rd = rectv(pos, frameSize);
    nvgRenderSubImage(context->gfx, sprite.image, rs, rd, scale);
}

GameSpriteFrame getSpriteFrame(GameContext* context, GameSprite sprite, s32 frameIndex)
{
    assert(sprite.image);
    assert(frameIndex >= 0 && frameIndex < sprite.framesCount);
    return sprite.frames[frameIndex];
}

void freeSprite(GameContext* context, GameSprite sprite)
{
    if (!sprite.image)
    {
        logWarning("Trying to free a sprite with image: %d\n", sprite.image);
        return;
    }

    for (s32 i = 0; i < sprite.framesCount; i++)
    {
        if (sprite.frames[i].data)
            free(sprite.frames[i].data);
    }

    nvgDeleteImage(context->gfx, sprite.image);
}