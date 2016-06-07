#pragma once

const int SCREEN_X_BLOCKS = 32;
const int SCREEN_Y_BLOCKS = 18;
const int BLOCK_PXSIZE = 60;
const int BLOCK_FACTOR = 100;

const int SCREEN_X_PXSIZE = SCREEN_X_BLOCKS * BLOCK_PXSIZE;
const int SCREEN_Y_PXSIZE = SCREEN_Y_BLOCKS * BLOCK_PXSIZE;

const int GRAVITY = 10;
const int SPEED = 5;
const int JUMP = 9;

static inline int bl(int block){
   return block * BLOCK_PXSIZE;
}

const int METER = 2*BLOCK_PXSIZE;

