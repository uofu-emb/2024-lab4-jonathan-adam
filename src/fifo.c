#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id) {
    struct request_msg data;
    for (;;) {
        xQueueReceive(requests, &data, portMAX_DELAY);
        data.output = data.input + 5;
        data.handled_by = id;
        xQueueSendToBack(results, &data, portMAX_DELAY);
    }
}