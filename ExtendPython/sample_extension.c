#include "Python.h"

static PyObject* ex_example1(PyObject *self, PyObject *args);
static PyObject* ex_example2(PyObject *self, PyObject *args);
static PyObject* ex_example3(PyObject *self, PyObject *args);
static PyObject* ex_example4(PyObject *self, PyObject *args);
static PyObject* ex_example5(PyObject *self, PyObject *args);
static PyObject* ex_example6(PyObject *self, PyObject *args);

static PyMethodDef ExMethods[] = {
    // method_name, func_ptr, arg_type, "description"
    {"func1",  ex_example1, METH_VARARGS, "do something"},
    {"func2",  ex_example2, METH_VARARGS, "do something"},
    {"func3",  ex_example3, METH_VARARGS, "do something"},
    {"func4",  ex_example4, METH_VARARGS, "do something"},
    {"func5",  ex_example5, METH_VARARGS, "do something"},
    {"func6",  ex_example6, METH_VARARGS, "do something"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef exmodule = {
    PyModuleDef_HEAD_INIT,
    "ex",     /* name of module */
    NULL,     /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    ExMethods
};

static PyObject *ExError;

PyMODINIT_FUNC
PyInit_ex(void)
{
    PyObject *m = PyModule_Create(&exmodule);

    if (m == NULL)
        return NULL;
 
    ExError = PyErr_NewException("ex.my_exception_name", NULL, NULL);
    Py_INCREF(ExError);
    PyModule_AddObject(m, "error", ExError);

    return m;
}

// defining function
static PyObject* ex_example1(PyObject *self, PyObject *args)
{
    fprintf(stderr, "%s is called\n", __func__);

    // returning NULL value will raise Exception
    return NULL;
}

// defining function (cont.)
static PyObject* ex_example2(PyObject *self, PyObject *args)
{
    fprintf(stderr, "%s is called\n", __func__);

    // equvalent to raise ex.my_exception_name("!!!")
    PyErr_SetString(ExError, "!!!");
    return NULL;
}

// correct way to define function
static PyObject* ex_example3(PyObject *self, PyObject *args)
{
    fprintf(stderr, "%s is called\n", __func__);
    Py_RETURN_NONE;
}

// passing argument and retuning value
static PyObject* ex_example4(PyObject *self, PyObject *args)
{
    PyObject* ret;
    PyObject* dummy;

    fprintf(stderr, "%s is called\n", __func__);
    ret = Py_BuildValue("i", 123);


    // trivial code: example of dereferencing object
    dummy = Py_BuildValue("i", 444);
    Py_DECREF(dummy);

    return ret;
}

// passing multiple arguments
static PyObject* ex_example5(PyObject *self, PyObject *args)
{
    const char *str;
    int i;

    if (!PyArg_ParseTuple(args, "si", &str, &i))
        return NULL;

    return Py_BuildValue("is", i, str);
}

// variadic example
static PyObject* ex_example6(PyObject *self, PyObject *args)
{
    const char *str = "???";
    int i = 666;

    if (!PyArg_ParseTuple(args, "|si", &str, &i))
        return NULL;

    return Py_BuildValue("is", i, str);
}
