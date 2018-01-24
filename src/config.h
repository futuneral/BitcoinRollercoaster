#ifndef _BTC_COASTER_CONFIG_H
#define _BTC_COASTER_CONFIG_H

// Number of data points on the graph
#define HISTORY_SIZE 20
// Graph width in pixels
#define GRAPH_WIDTH 150
// Graph height in pixels
#define GRAPH_HEIGHT 80
// Max cart rotation angle
#define MAX_ANGLE 60.0f
// Number of degrees to turn when price changes by 1% over the length of the graph
#define DEGREE_PER_PERCENT 30.0f
// Value (in degrees) for correcting mechanical imperfections (i.e. when card is not level in the mid position)
#define MECHANICAL_OFFSET 0
// Time between refreshes
#define REFRESH_DELAY 300000

#define GRAPH_WIDTH 128
#define GRAPH_HEIGHT 20

// Screen width in pixels
#define SCREEN_WIDTH 128
// Screen height in pixels
#define SCREEN_HEIGHT 63

#define SPEED_DEG_PER_S 20.0f
#define CART_PIN 13

#define DEMO_MODE false


#endif
