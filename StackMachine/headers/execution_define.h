#ifndef STACKMACHINE_EXECUTION_DEFINE_H
#define STACKMACHINE_EXECUTION_DEFINE_H

#define EXECUTE_OPERATION(expression, action) \
    if (expression) { \
        action \
        return; \
        }

#endif //STACKMACHINE_EXECUTION_DEFINE_H
