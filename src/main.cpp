#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern "C" {
#include "soundpipe.h"
}

typedef struct {
    sp_osc *osc;
    sp_ftbl *ft;
} UserData;

void write_osc(sp_data *sp, void *udata) {
    UserData *ud = static_cast<UserData*>(udata);
    sp_osc_compute(sp, ud->osc, NULL, &sp->out[0]);
}

int main() {
    UserData ud;
    sp_data *sp;
    sp_create(&sp);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_osc_create(&ud.osc);

    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0.0);
    ud.osc->freq = 500;
    sp->len = 44100 * 5;

    sp_wavout *wavout = nullptr;
    sp_wavout_create(&wavout);
    sp_wavout_init(sp, wavout, "test.wav");
    for( ; ; ) {
        if(sp->len == 0) { break; }
        sp->len -= 1;

        write_osc(sp, &ud);
        SPFLOAT dest = 0.0;
        sp_wavout_compute(sp, wavout, &sp->out[0], &dest);
    }

    sp_wavout_destroy(&wavout);

    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_destroy(&sp);

    return 0;
}
