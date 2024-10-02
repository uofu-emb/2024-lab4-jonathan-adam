#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id) {
    struct request_msg data;
    for (;;) {
        if (xQueueReceive(requests, &data, portMAX_DELAY) == pdTRUE) {
            data.output = data.input + 5;
            data.handled_by = id;
            if (xQueueSendToBack(results, &data, portMAX_DELAY) != pdTRUE) {
                printf("Failed to send data:\n\tInput: %d\n\tOutput: %d\n\tHandled by: %u\n",
                       data.input, data.output, data.handled_by);
            }
        }
        else {
            printf("Failed to receive request (id=%d)\n", id);
        }
    }
}