class _st7789 {
public:
   enum class commands : uint8_t {
      NOP        = 0x00,
      SWRESET    = 0x01,
      RDDID      = 0x04,
      RDDST      = 0x09,
      RDDPM      = 0x0A,
      RDDMADCTL  = 0x0B,
      RDDIM      = 0x0D,
      RDDSEM     = 0x0E,
      RDDSDR     = 0x0F,

      SLPIN      = 0x10,
      SLPOUT     = 0x11,
      PTLON      = 0x12,
      NORON      = 0x13,

      INVOFF     = 0x20,
      INVON      = 0x21,
      GAMSET     = 0x26,
      DISPOFF    = 0x28,
      DISPON     = 0x29,
      CASET      = 0x2A,
      RASET      = 0x2B,
      RAMWR      = 0x2C,
      RAMRD      = 0x2E,

      PTLAR      = 0x30,
      VSCRDEF    = 0x33,
      TEOFF      = 0x34,
      TEON       = 0x35,
      MADCTL     = 0x36,
      COLMOD     = 0x3A
   };   
};