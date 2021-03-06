/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file Gyroscope driver interface.
 */

#ifndef _DRV_GYRO_H
#define _DRV_GYRO_H

#include <stdint.h>
#include <sys/ioctl.h>

#include "drv_orb_dev.h"

#define GYRO_DEVICE_PATH	"/dev/gyro"

/**
 * gyro report structure.  Reads from the device must be in multiples of this
 * structure.
 */
struct gyro_report {
	float x;
	float y;
	float z;
	uint64_t timestamp;
};

/** gyro scaling factors; Vout = (Vin * Vscale) + Voffset */
struct gyro_scale {
	float	x_offset;
	float	x_scale;
	float	y_offset;
	float	y_scale;
	float	z_offset;
	float	z_scale;
};

/*
 * ObjDev tag for raw gyro data.
 */
ORB_DECLARE(sensor_gyro);

/*
 * ioctl() definitions
 */

#define _GYROIOCBASE		(0x2200)
#define _GYROIOC(_n)		(_IOC(_GYROIOCBASE, _n))

/** set the driver polling rate to (arg) Hz, or one of the GYRO_POLLRATE constants */
#define GYROIOCSPOLLRATE	_GYROIOC(0)

#define GYRO_POLLRATE_MANUAL		1000000	/**< poll when read */
#define GYRO_POLLRATE_EXTERNAL		1000001	/**< poll when device signals ready */

/** set the internal queue depth to (arg) entries, must be at least 1 */
#define GYROIOCSQUEUEDEPTH	_GYROIOC(1)

/** set the gyro internal sample rate to at least (arg) Hz */
#define GYROIOCSSAMPLERATE	_GYROIOC(2)

/** set the gyro internal lowpass filter to no lower than (arg) Hz */
#define GYROIOCSLOWPASS		_GYROIOC(3)

/** set the report format to (arg); zero is the standard, 1-10 are reserved, all others are driver-specific. */
#define GYROIOCSREPORTFORMAT	_GYROIOC(4)

/** set the gyro scaling constants to (arg) */
#define GYROIOCSSCALE		_GYROIOC(5)

#endif /* _DRV_GYRO_H */
