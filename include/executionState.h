#ifndef Execution_state_h
#define Execution_state_h

typedef enum ExecutionState
{
	EXE_ERROR,
	EXE_OK,
	EXE_ABORT,
	EXE_WARNING,
	EXE_WAIT,
} ExecutionState;
#endif