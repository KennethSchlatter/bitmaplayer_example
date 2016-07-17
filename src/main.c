#include <pebble.h>

// Create a window to put everything in
static Window *main_window;

// Create a layer for the "bitmap" image
static BitmapLayer *bitmap_layer;
  
// Create a "bitmap" image to put in the BitmapLayer
static GBitmap *bitmap_image; // Always remember the semicolons

// Load the window and 
static void main_window_load(Window *window) {
  
// Set the window's bakcground color. For this demo, we're setting the background color to white.
  window_set_background_color(main_window, GColorWhite);
  
// Get the dimensions of the screen, which are called the bounds
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  
// Set the resource image to be used in the bitmap layer
  bitmap_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_RESOURCE);
    // This resource is set up to be different for each platform, so it will look good on both Color and Black & White displayer
  
// Set the size of the bitmap layer to the size of the screen, or the "bounds"
  bitmap_layer = bitmap_layer_create(bounds);
  
// Put the bitmap image in the bitmap layer
  bitmap_layer_set_bitmap(bitmap_layer, bitmap_image);
  
// Put the image in the center of the screen
  bitmap_layer_set_alignment(bitmap_layer, GAlignCenter);
  
// Set the compositing mode so that transparent images are transparent
  bitmap_layer_set_compositing_mode(bitmap_layer, GCompOpSet);
    
// Add the bitmap layer to the window
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bitmap_layer));
}

// Unload everything when the app closes
static void main_window_unload(Window *window) {
  
  // Unload the bitmap layer
  bitmap_layer_destroy(bitmap_layer);
}

// Initialize everything
static void init() {
  
// Create the main window
  main_window = window_create();
  
// Set the window handlers to load and unload the window
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
// Push the window so it can be seen
  window_stack_push(main_window, true);
}

// Deinitialize everything so the app will close properly
static void deinit() {
  
// Deinitialize the window and everything in it
  window_destroy(main_window);
}

// Make everything run in the right order
int main(void){
  init();
  app_event_loop();
  deinit();
}