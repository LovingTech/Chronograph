# Arduino-Chronograph
## Code of an Arduino chronograph.
You can configure the distance from the two sensors(begining and end).
``` 
// convert mm/s to kph
kph = ((750000000 / elapsed_time) * 0.00036); 
```
In the current configuration the distance between sensors is 7.5cm or 750mm
