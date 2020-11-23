//
// WIP
// Copyright (c) 2020 Jovan Lanik
//

// Input Functions

#include <unistd.h>

#include "wip_types.h"
#include "wip_input.h"

struct WIP_FIFO(WIP_KEY_BUFFER, wip_key_t) wip_key;

int wip_writeKey(wip_key_t key) {
	int a;
	for(a = WIP_INPUT_ATTEMPTS; a > 0; --a)
		if(wip_key.head + 1 != wip_key.tail) break;
		else sleep(WIP_INPUT_SLEEP);
	if(a == 0) return 0;
	wip_key.head = (wip_key.head + 1) % WIP_KEY_BUFFER;
	wip_key.buffer[wip_key.head] = key;
	return 1;
}

wip_key_t wip_readKey(void) {
	if(wip_key.head == wip_key.tail)
		return (wip_key_t){ 0, -1 };
	wip_key.tail = (wip_key.tail + 1) % WIP_KEY_BUFFER;
	return wip_key.buffer[wip_key.tail];
}

