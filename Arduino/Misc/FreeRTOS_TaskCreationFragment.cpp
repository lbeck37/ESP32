/*-----------------------------------------------------------
 * TASK CREATION API
 *----------------------------------------------------------*/
/**
 * Create a new task with a specified affinity.
 *
 * This function is similar to xTaskCreate, but allows setting task affinity
 * in SMP system.
 *
 * @param pvTaskCode Pointer to the task entry function.  Tasks
 * must be implemented to never return (i.e. continuous loop).
 *
 * @param pcName A descriptive name for the task.  This is mainly used to
 * facilitate debugging.  Max length defined by configMAX_TASK_NAME_LEN - default
 * is 16.
 *
 * @param usStackDepth The size of the task stack specified as the number of
 * bytes. Note that this differs from vanilla FreeRTOS.
 *
 * @param pvParameters Pointer that will be used as the parameter for the task
 * being created.
 *
 * @param uxPriority The priority at which the task should run.  Systems that
 * include MPU support can optionally create tasks in a privileged (system)
 * mode by setting bit portPRIVILEGE_BIT of the priority parameter.  For
 * example, to create a privileged task at priority 2 the uxPriority parameter
 * should be set to ( 2 | portPRIVILEGE_BIT ).
 *
 * @param pvCreatedTask Used to pass back a handle by which the created task
 * can be referenced.
 *
 * @param xCoreID If the value is tskNO_AFFINITY, the created task is not
 * pinned to any CPU, and the scheduler can run it on any core available.
 * Other values indicate the index number of the CPU which the task should
 * be pinned to. Specifying values larger than (portNUM_PROCESSORS - 1) will
 * cause the function to fail.
 *
 * @return pdPASS if the task was successfully created and added to a ready
 * list, otherwise an error code defined in the file projdefs.h
 *
 * \ingroup Tasks
 */
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
  BaseType_t xTaskCreatePinnedToCore( TaskFunction_t pvTaskCode,
                    const char * const pcName,
                    const uint32_t usStackDepth,
                    void * const pvParameters,
                    UBaseType_t uxPriority,
                    TaskHandle_t * const pvCreatedTask,
                    const BaseType_t xCoreID);

#endif
/**
 * Create a new task and add it to the list of tasks that are ready to run.
 *
 * Internally, within the FreeRTOS implementation, tasks use two blocks of
 * memory.  The first block is used to hold the task's data structures.  The
 * second block is used by the task as its stack.  If a task is created using
 * xTaskCreate() then both blocks of memory are automatically dynamically
 * allocated inside the xTaskCreate() function.  (see
 * http://www.freertos.org/a00111.html).  If a task is created using
 * xTaskCreateStatic() then the application writer must provide the required
 * memory.  xTaskCreateStatic() therefore allows a task to be created without
 * using any dynamic memory allocation.
 *
 * See xTaskCreateStatic() for a version that does not use any dynamic memory
 * allocation.
 *
 * xTaskCreate() can only be used to create a task that has unrestricted
 * access to the entire microcontroller memory map.  Systems that include MPU
 * support can alternatively create an MPU constrained task using
 * xTaskCreateRestricted().
 *
 * @param pvTaskCode Pointer to the task entry function.  Tasks
 * must be implemented to never return (i.e. continuous loop).
 *
 * @param pcName A descriptive name for the task.  This is mainly used to
 * facilitate debugging.  Max length defined by configMAX_TASK_NAME_LEN - default
 * is 16.
 *
 * @param usStackDepth The size of the task stack specified as the number of
 * bytes. Note that this differs from vanilla FreeRTOS.
 *
 * @param pvParameters Pointer that will be used as the parameter for the task
 * being created.
 *
 * @param uxPriority The priority at which the task should run.  Systems that
 * include MPU support can optionally create tasks in a privileged (system)
 * mode by setting bit portPRIVILEGE_BIT of the priority parameter.  For
 * example, to create a privileged task at priority 2 the uxPriority parameter
 * should be set to ( 2 | portPRIVILEGE_BIT ).
 *
 * @param pvCreatedTask Used to pass back a handle by which the created task
 * can be referenced.
 *
 * @return pdPASS if the task was successfully created and added to a ready
 * list, otherwise an error code defined in the file projdefs.h
 *
 * @note If program uses thread local variables (ones specified with "__thread" keyword)
 * then storage for them will be allocated on the task's stack.
 *
 * Example usage:
 * @code{c}
 *  // Task to be created.
 *  void vTaskCode( void * pvParameters )
 *  {
 *   for( ;; )
 *   {
 *       // Task code goes here.
 *   }
 *  }
 *
 *  // Function that creates a task.
 *  void vOtherFunction( void )
 *  {
 *  static uint8_t ucParameterToPass;
 *  TaskHandle_t xHandle = NULL;
 *
 *   // Create the task, storing the handle.  Note that the passed parameter ucParameterToPass
 *   // must exist for the lifetime of the task, so in this case is declared static.  If it was just an
 *   // an automatic stack variable it might no longer exist, or at least have been corrupted, by the time
 *   // the new task attempts to access it.
 *   xTaskCreate( vTaskCode, "NAME", STACK_SIZE, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );
 *      configASSERT( xHandle );
 *
 *   // Use the handle to delete the task.
 *      if( xHandle != NULL )
 *      {
 *       vTaskDelete( xHandle );
 *      }
 *  }
 * @endcode
 * \ingroup Tasks
 */
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
  static inline IRAM_ATTR BaseType_t xTaskCreate(
      TaskFunction_t pvTaskCode,
      const char * const pcName,
      const uint32_t usStackDepth,
      void * const pvParameters,
      UBaseType_t uxPriority,
      TaskHandle_t * const pvCreatedTask)
  {
    return xTaskCreatePinnedToCore( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pvCreatedTask, tskNO_AFFINITY );
  }
#endif
