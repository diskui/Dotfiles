/* See LICENSE file for copyright and license details. */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../slstatus.h"
#include "../util.h"

#if defined(ALSA)
	#include <alsa/asoundlib.h>

	static const char *devname = "default";
	const char *
	vol_perc(const char *mixname)
	{
		snd_mixer_t *mixer = NULL;
		snd_mixer_selem_id_t *mixid = NULL;
		snd_mixer_elem_t *elem = NULL;
		long min = 0, max = 0, volume = -1;
		int err;

		if ((err = snd_mixer_open(&mixer, 0))) {
			warn("snd_mixer_open: %d", err);
			return NULL;
		}
		if ((err = snd_mixer_attach(mixer, devname))) {
			warn("snd_mixer_attach(mixer, \"%s\"): %d", devname, err);
			goto cleanup;
		}
		if ((err = snd_mixer_selem_register(mixer, NULL, NULL))) {
			warn("snd_mixer_selem_register(mixer, NULL, NULL): %d", err);
			goto cleanup;
		}
		if ((err = snd_mixer_load(mixer))) {
			warn("snd_mixer_load(mixer): %d", err);
			goto cleanup;
		}

		snd_mixer_selem_id_alloca(&mixid);
		snd_mixer_selem_id_set_name(mixid, mixname);
		snd_mixer_selem_id_set_index(mixid, 0);

		elem = snd_mixer_find_selem(mixer, mixid);
		if (!elem) {
			warn("snd_mixer_find_selem(mixer, \"%s\") == NULL", mixname);
			goto cleanup;
		}

		if ((err = snd_mixer_selem_get_playback_volume_range(elem, &min, &max))) {
			warn("snd_mixer_selem_get_playback_volume_range(): %d", err);
			goto cleanup;
		}
		if ((err = snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume))) {
			warn("snd_mixer_selem_get_playback_volume(): %d", err);
		}

	cleanup:
		snd_mixer_free(mixer);
		snd_mixer_detach(mixer, devname);
		snd_mixer_close(mixer);

		return volume == -1 ? NULL : bprintf("%.0f", (volume-min)*100./(max-min));
	}
#else
	#include <sys/soundcard.h>

	const char *
	vol_perc(const char *card)
	{
		size_t i;
		int v, afd, devmask;
		char *vnames[] = SOUND_DEVICE_NAMES;

		if ((afd = open(card, O_RDONLY | O_NONBLOCK)) < 0) {
			warn("open '%s':", card);
			return NULL;
		}

		if (ioctl(afd, (int)SOUND_MIXER_READ_DEVMASK, &devmask) < 0) {
			warn("ioctl 'SOUND_MIXER_READ_DEVMASK':");
			close(afd);
			return NULL;
		}
		for (i = 0; i < LEN(vnames); i++) {
			if (devmask & (1 << i) && !strcmp("vol", vnames[i])) {
				if (ioctl(afd, MIXER_READ(i), &v) < 0) {
					warn("ioctl 'MIXER_READ(%ld)':", i);
					close(afd);
					return NULL;
				}
			}
		}

		close(afd);

		return bprintf("%d", v & 0xff);
	}
#endif
