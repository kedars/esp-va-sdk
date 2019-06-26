/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2018 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _RING_BUF_H_
#define _RING_BUF_H_

#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RB_FAIL ESP_FAIL
#define RB_ABORT -1
#define RB_WRITER_FINISHED -2
#define RB_READER_UNBLOCK -3

typedef struct ringbuf {
    char *name;
    uint8_t *base;        /**< Original pointer */
    /* XXX: these need to be volatile? */
    uint8_t *volatile readptr;   /**< Read pointer */
    uint8_t *volatile writeptr;   /**< Write pointer */
    volatile ssize_t fill_cnt;  /**< Number of filled slots */
    ssize_t size;       /**< Buffer size */
    xSemaphoreHandle can_read;
    xSemaphoreHandle can_write;
    xSemaphoreHandle lock;
    int abort_read;
    int abort_write;
    int writer_finished;  //to prevent infinite blocking for buffer read
    int reader_unblock;
} ringbuf_t;

ringbuf_t *rb_init(const char *rb_name, uint32_t size);
void rb_abort_read(ringbuf_t *rb);
void rb_abort_write(ringbuf_t *rb);
void rb_abort(ringbuf_t *rb);
void rb_reset(ringbuf_t *rb);
/**
 * @brief Special function to reset the buffer while keeping rb_write aborted.
 *        This rb needs to be reset again before being useful.
 */
void rb_reset_and_abort_write(ringbuf_t *rb);
void rb_stat(ringbuf_t *rb);
ssize_t rb_filled(ringbuf_t *rb);
ssize_t rb_available(ringbuf_t *rb);
int rb_read(ringbuf_t *rb, uint8_t *buf, int len, uint32_t ticks_to_wait);
int rb_write(ringbuf_t *rb, uint8_t *buf, int len, uint32_t ticks_to_wait);
void rb_cleanup(ringbuf_t *rb);
void rb_signal_writer_finished(ringbuf_t *rb);
void rb_wakeup_reader(ringbuf_t *rb);
int rb_is_writer_finished(ringbuf_t *rb);

#ifdef __cplusplus
}
#endif

#endif
