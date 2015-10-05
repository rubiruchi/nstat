/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford
 * Junior University
 *
 * We are making the OpenFlow specification and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * The name and trademarks of copyright holder(s) may NOT be used in
 * advertising or publicity pertaining to the Software or any
 * derivatives without specific, written prior permission.
 */

#include <config.h>
#include "bitmap.h"
#include <string.h>

/* Sets 'count' consecutive bits in 'bitmap', starting at bit offset 'start',
 * to 'value'. */
void
bitmap_set_multiple(unsigned long *bitmap, size_t start, size_t count,
                    bool value)
{
    for (; count && start % BITMAP_ULONG_BITS; count--) {
        bitmap_set(bitmap, start++, value);
    }
    for (; count >= BITMAP_ULONG_BITS; count -= BITMAP_ULONG_BITS) {
        *bitmap_unit__(bitmap, start) = -(unsigned long) value;
        start += BITMAP_ULONG_BITS;
    }
    for (; count; count--) {
        bitmap_set(bitmap, start++, value);
    }
}

/* Compares the 'n' bits in bitmaps 'a' and 'b'.  Returns true if all bits are
 * equal, false otherwise. */
bool
bitmap_equal(const unsigned long *a, const unsigned long *b, size_t n)
{
    size_t i;

    if (memcmp(a, b, n / BITMAP_ULONG_BITS * sizeof(unsigned long))) {
        return false;
    }
    for (i = ROUND_DOWN(n, BITMAP_ULONG_BITS); i < n; i++) {
        if (bitmap_is_set(a, i) != bitmap_is_set(b, i)) {
            return false;
        }
    }
    return true;
}
