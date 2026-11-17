# Compiler control set

Chosen by `tools/toolchains/pick_control.py` from source text only (no scores); its
docstring states the rule. Universe: 4713 `@implements` functions outside src/control/;
size tertile cut points: S < 5 code lines <= M < 10 <= L.
Select-bearing (uses `?:`, directly or via a same-file macro): 20 of 60 chosen.

The sources are scored where they stand; nothing is copied or edited.

| # | file | address | function | module | lang | size | select |
|---|------|---------|----------|--------|------|------|--------|
| 1 | src/race/CamTV.cpp | 0x0802f0 | _ZN7CamCtrl6CCamTV8f_0802f0Ev | race | C++ | M 5 |  |
| 2 | src/race/CarMatrix.c | 0x0a6e4c | f_0a6e4c | race | C | M 5 |  |
| 3 | src/race/CarMatrix.c | 0x0a6e84 | f_0a6e84 | race | C | L 10 |  |
| 4 | src/race/CarPhysics.cpp | 0x0a9134 | f_0a9134 | race | C++ | M 5 | yes |
| 5 | src/race/ComcarPace.c | 0x0fd6d4 | f_0fd6d4 | race | C | S 4 |  |
| 6 | src/race/EventJob.cpp | 0x0d49c4 | _ZN3Map5Event9CLeafWork5Setup | race | C++ | L 27 |  |
| 7 | src/race/LeafLoopStop.c | 0x0ec35c | f_0ec35c | race | C | S 4 |  |
| 8 | src/race/Race2DPieces.cpp | 0x102cf0 | C2DTimeLimit8f_101b54 | race | C++ | L 14 |  |
| 9 | src/race/Race2DPieces.cpp | 0x104484 | C2DFlag8f_101b54 | race | C++ | M 5 |  |
| 10 | src/race/Race2DPieces.cpp | 0x1078a0 | C2DLapTime8f_101f64 | race | C++ | S 1 |  |
| 11 | src/race/Race2DPieces.cpp | 0x1078b0 | C2DLapTime8f_101f6c | race | C++ | S 1 |  |
| 12 | src/race/RaceRandom.c | 0x0c2c44 | f_0c2c44 | race | C | L 76 | yes |
| 13 | src/race/RidgeNetcar.cpp | 0x0c1b80 | f_0c1b80 | race | C++ | L 45 | yes |
| 14 | src/race/RidgeNetcar.cpp | 0x0c23d8 | f_0c23d8 | race | C++ | L 17 | yes |
| 15 | src/race/RidgeNetcar.cpp | 0x0c28e4 | f_0c28e4 | race | C++ | M 8 | yes |
| 16 | src/race/SpeedUnit.c | 0x06b6fc | f_06b6fc | race | C | M 5 |  |
| 17 | src/race/SpeedUnit.c | 0x06b748 | f_06b748 | race | C | L 26 |  |
| 18 | src/rrbios/TextureInfo.cpp | 0x0233dc | f_0233dc | rrbios | C++ | M 7 |  |
| 19 | src/rrbios/TextureInfo.cpp | 0x023cf8 | _GLOBAL__I_ | rrbios | C++ | S 1 |  |
| 20 | src/rrbios/TextureInfo.cpp | 0x0242a8 | _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE4HashEj | rrbios | C++ | M 5 |  |
| 21 | src/rrbios/TextureInfo.cpp | 0x02435c | _ZN12CKeyLinkListIN6RRBios14TextureManager5CInfoEED1Ev | rrbios | C++ | S 1 |  |
| 22 | src/rrbios/TextureLists.c | 0x02482c | f_02482c | rrbios | C | L 12 |  |
| 23 | src/rrbios/TextureLists.c | 0x024918 | f_024918 | rrbios | C | M 5 |  |
| 24 | src/rrbios/TextureLists.c | 0x024930 | f_024930 | rrbios | C | L 19 |  |
| 25 | src/rrbios/TextureLists.c | 0x024a28 | f_024a28 | rrbios | C | M 6 |  |
| 26 | src/rrbios/TextureManager.cpp | 0x022f54 | f_022f54 | rrbios | C++ | L 23 |  |
| 27 | src/rrbios/TextureManager.cpp | 0x023038 | f_023038 | rrbios | C++ | L 14 |  |
| 28 | src/sequence/FadeColourState.c | 0x0e9e08 | f_0e9e08 | sequence | C | M 8 |  |
| 29 | src/sequence/FadeColourState.c | 0x0e9e48 | f_0e9e48 | sequence | C | S 4 |  |
| 30 | src/sequence/MenuData.cpp | 0x078600 | _ZN6Select21CCarGetNumberMenuDataD0Ev | sequence | C++ | S 4 |  |
| 31 | src/sequence/OptionModeJob.cpp | 0x014754 | f_014754 | sequence | C++ | L 13 |  |
| 32 | src/sequence/PauseMenuName.cpp | 0x093680 | f_093680 | sequence | C++ | L 22 | yes |
| 33 | src/sequence/RallyXSetup.cpp | 0x0e798c | f_0e798c | sequence | C++ | M 7 |  |
| 34 | src/sequence/SequenceManager.cpp | 0x003830 | f_003830 | sequence | C++ | M 9 | yes |
| 35 | src/sequence/SequenceManager.cpp | 0x003860 | f_003860 | sequence | C++ | M 9 | yes |
| 36 | src/sequence/SequenceManager.cpp | 0x004864 | f_004864 | sequence | C++ | L 17 | yes |
| 37 | src/sequence/SpriteDisplayList.c | 0x0e7a10 | f_0e7a10 | sequence | C | L 13 |  |
| 38 | src/sound/Bgm.cpp | 0x09666c | f_09666c | sound | C++ | L 31 | yes |
| 39 | src/sound/EngineCurve.c | 0x0ca1a8 | f_0ca1a8 | sound | C | L 80 | yes |
| 40 | src/sound/RaceSound.cpp | 0x01d994 | f_01d994 | sound | C++ | L 26 |  |
| 41 | src/sound/RaceVoice.cpp | 0x092d10 | f_092d10 | sound | C++ | S 4 |  |
| 42 | src/sound/RadioPlayer.cpp | 0x0f6f2c | f_0f6f2c | sound | C++ | M 6 | yes |
| 43 | src/sound/SasVoice.c | 0x10edf8 | f_10edf8 | sound | C | M 6 |  |
| 44 | src/sound/SasVoice.c | 0x10f73c | f_10f73c | sound | C | L 38 |  |
| 45 | src/sound/SoundDelayQueue.cpp | 0x10eaec | f_10eaec | sound | C++ | M 8 |  |
| 46 | src/sound/SoundMath.c | 0x1157f0 | f_1157f0 | sound | C | S 4 |  |
| 47 | src/sound/StreamBase.cpp | 0x0954ac | f_0954ac | sound | C++ | L 11 | yes |
| 48 | src/sound/StreamBase.cpp | 0x095624 | f_095624 | sound | C++ | M 8 | yes |
| 49 | src/sound/StreamChannelThreads.c | 0x112b70 | f_112b70 | sound | C | L 22 | yes |
| 50 | src/sound/StreamChannels.c | 0x1116e0 | f_1116e0 | sound | C | M 5 | yes |
| 51 | src/system/FastMath.c | 0x099e7c | f_099e7c | system | C | L 16 |  |
| 52 | src/system/GamePacketProc.cpp | 0x0838e4 | _ZN5QueueI5Rec16E4LastEPS0_ | system | C++ | M 9 | yes |
| 53 | src/system/GraphicsDraw.cpp | 0x02261c | f_02261c | system | C++ | L 25 |  |
| 54 | src/system/Matrix44.cpp | 0x09b828 | _ZN5Mat44C2EPA4_Kf | system | C++ | S 1 |  |
| 55 | src/system/MoviePlayer.cpp | 0x08c21c | _ZN11CMovieArena10GetAlignedEii | system | C++ | M 9 | yes |
| 56 | src/system/StackHeap.c | 0x099710 | f_099710 | system | C | S 4 |  |
| 57 | src/system/SwgPlayer.cpp | 0x064d8c | f_064d8c | system | C++ | L 38 | yes |
| 58 | src/system/SwgPlayer.cpp | 0x067788 | f_067788 | system | C++ | L 17 | yes |
| 59 | src/system/SwgPlayer.cpp | 0x0698b8 | f_0698b8 | system | C++ | M 5 |  |
| 60 | src/system/VectorInline.c | 0x0a6248 | f_0a6248 | system | C | M 8 |  |
