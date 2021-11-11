# Arduino-Chronograph
## Code of an Arduino chronograph.
Designed for an Arduino Uno. I used two laser gates and two 3D printed holders.
You can configure the distance from the two sensors(begining and end).
``` 
// convert mm/s to kph
kph = ((750000000 / elapsed_time) * 0.00036); 
```
In the current configuration the distance between sensors is 7.5cm or 750mm

You can make the samething by printing the part twice and buying an IR break beam (https://www.adafruit.com/product/2168)
