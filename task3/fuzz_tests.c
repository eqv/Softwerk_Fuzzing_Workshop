#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#include "lodepng/lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  unsigned error = 0;
  unsigned char* image = NULL;
  unsigned width = 0, height = 0;
  LodePNGState state;

  lodepng_state_init(&state);
  state.decoder.ignore_crc = 1;
  state.decoder.zlibsettings.ignore_adler32 = 1;
  /*optionally customize the state*/

  error = lodepng_decode(&image, &width, &height, &state, Data, Size);
  //if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
  if(!error){
    unsigned char* png = NULL;
    size_t pngsize = 0;

    error = lodepng_encode32(&png, &pngsize, image, width, height);
    //if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
    free(png);
  }

  lodepng_state_cleanup(&state);
  free(image);
  return 0;
}
