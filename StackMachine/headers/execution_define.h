#ifndef STACKMACHINE_EXECUTION_DEFINE_H
#define STACKMACHINE_EXECUTION_DEFINE_H

#define EXECUTE_OPERATION(expression, action) \
    if (expression) { \
        action \
        continue; \
        }

#endif //STACKMACHINE_EXECUTION_DEFINE_H
