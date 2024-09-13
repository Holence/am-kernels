# Navy那边编译后要放入ramdisk，需要体积小一点
ifeq ($(AM_HOME), $(NAVY_HOME))
  VIDEO_ROW = 48
  VIDEO_COL = 64
  AUDIO_FREQ = 11025
else
  VIDEO_ROW = 96
  VIDEO_COL = 128
  AUDIO_FREQ = 44100
endif

AUDIO_CHANNEL = 1

VIDEO_SRC = bad-apple.mp4
VIDEO = build/video.frame
AUDIO = build/audio.pcm

NAME = bad-apple
SRCS = bad-apple.c resources.S
include $(AM_HOME)/Makefile

CFLAGS  += -DVIDEO_ROW=$(VIDEO_ROW) -DVIDEO_COL=$(VIDEO_COL) \
           -DAUDIO_FREQ=$(AUDIO_FREQ) -DAUDIO_CHANNEL=$(AUDIO_CHANNEL)
ASFLAGS += -DVIDEO_FILE=\"$(abspath $(VIDEO))\" -DAUDIO_FILE=\"$(abspath $(AUDIO))\"
$(VIDEO):
	ffmpeg -i $(VIDEO_SRC) -f image2pipe -s $(VIDEO_COL)x$(VIDEO_ROW) -vcodec rawvideo -pix_fmt monow $@

$(AUDIO):
	ffmpeg -i $(VIDEO_SRC) -vn -acodec pcm_s16le -f s16le -ac $(AUDIO_CHANNEL) -ar $(AUDIO_FREQ) $@

resources.S: $(VIDEO) $(AUDIO)
