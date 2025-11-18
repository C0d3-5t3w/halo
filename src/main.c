#include <stdio.h>
#include "lib/config/settings.h"
#include "root.h"

fn main(vd) {
    SETTINGS();
    while (1) {
        start_server();        // Main loop logic
    }
    return 0;
}
