void audioDataCallback(ma_device* sfx, void* output, const void* input, u32 sampleCount)
{
    NOT_USED(input);

    GameContext* context = (GameContext*)sfx->pUserData;
    if (!context)
    {
        return;
    }

    s16* outputStream = (s16*)output;

    // output audio here
}

bool initAudio(GameContext* context)
{
    ma_device_config sfxConfig;
    sfxConfig = ma_device_config_init(ma_device_type_playback);
    sfxConfig.playback.format = ma_format_s16;
    sfxConfig.playback.channels = 1;
    sfxConfig.playback.shareMode = ma_share_mode_shared;
    sfxConfig.sampleRate = PLAYBACK_FREQ;
    sfxConfig.dataCallback = audioDataCallback;
    sfxConfig.pUserData = context;

    if (ma_device_init(NULL, &sfxConfig, &context->sfx) != MA_SUCCESS)
    {
        logError("Failed to open playback device.\n");
        return false;
    }

    if (ma_device_start(&context->sfx) != MA_SUCCESS)
    {
        logError("Failed to start playback device.\n");
        ma_device_uninit(&context->sfx);
        return false;
    }

    return true;
}
