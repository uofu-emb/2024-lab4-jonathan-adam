#include "signal.h"

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data) {
    if (xSemaphoreTake(request, portMAX_DELAY) == pdTRUE) {
        data->output = data->input + 5;
        if (xSemaphoreGive(response) != pdTRUE) {
            printf("Failed to release response semaphore!\n");
        }
    }
    else {
        printf("Failed to obtain request semaphore!\n");
    }
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data) {
    if (xSemaphoreGive(request) != pdTRUE) {
        printf("Failed to release request semaphore!\n");
    }
    return xSemaphoreTake(response, 100);
}