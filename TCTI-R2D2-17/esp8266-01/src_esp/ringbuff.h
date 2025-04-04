#ifndef SRC_RINGBUFF_H
#define SRC_RINGBUFF_H

#ifdef __cplusplus
  extern "C" {
#endif /* c++ */

/* -------------------------------- Objects --------------------------------- */

struct RingBuff {
  int size;
  int element_size;
  void *read_it;
  void *write_it;
  void *data;
  void *end;
};


/* -------------------------------- Interface ------------------------------- */

/**
 * @brief 
 *  This functions initializes a Ringbuff struct.
 * @details
 *  This function does not check parameters and does not allocate memory.
 * @retval
 *  Returns zero on success.
 */
int RingBuffInit(struct RingBuff *buff, int size, int element_size, void *data);

/**
 * @brief 
 *  Loads data from buffer to address at dst.
 * @retval
 *  Returns number of bytes read.
 */
int RingBuffRead(struct RingBuff *buff, int num_to_read, void *dst);

/**
 * @brief 
 *  Writes from src into buffer.
 * @retval
 *  Returns number of bytes written.
 */
int RingBuffWrite(struct RingBuff *buff, int num_to_write, void *src);

/**
 * @brief
 *  Returns read_it in number of elements.
 */
int RingBuffGetReadItt(struct RingBuff *buff);

/**
 * @brief
 *  Returns write_it in number of elements.
 */
int RingBuffGetWriteItt(struct RingBuff *buff);


#ifdef __cplusplus
  };
#endif /* c++ */

#endif /* SRC_RINGBUFF_H */
