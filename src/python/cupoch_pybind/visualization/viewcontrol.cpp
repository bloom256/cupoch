#include "cupoch/io/class_io/ijson_convertible_io.h"
#include "cupoch/visualization/visualizer/view_control.h"
#include "cupoch_pybind/docstring.h"
#include "cupoch_pybind/visualization/visualization.h"
#include "cupoch_pybind/visualization/visualization_trampoline.h"

using namespace cupoch;

// Functions have similar arguments, thus the arg docstrings may be shared
static const std::unordered_map<std::string, std::string>
        map_view_control_docstrings = {
                {"parameter", "The pinhole camera parameter to convert from."},
                {"scale", "Scale ratio."},
                {"x", "Distance the mouse cursor has moved in x-axis."},
                {"y", "Distance the mouse cursor has moved in y-axis."},
                {"xo", "Original point coordinate of the mouse in x-axis."},
                {"yo", "Original point coordinate of the mouse in y-axis."},
                {"step", "The step to change field of view."},
                {"z_near", "The depth of the near z-plane of the visualizer."},
                {"z_far", "The depth of the far z-plane of the visualizer."},
};

void pybind_viewcontrol(py::module &m) {
    py::class_<visualization::ViewControl, PyViewControl<>,
               std::shared_ptr<visualization::ViewControl>>
            viewcontrol(m, "ViewControl", "View controller for visualizer.");
    py::detail::bind_default_constructor<visualization::ViewControl>(
            viewcontrol);
    viewcontrol
            .def("__repr__",
                 [](const visualization::ViewControl &vc) {
                     return std::string("ViewControl");
                 })
            .def(
                    "convert_to_pinhole_camera_parameters",
                    [](visualization::ViewControl &vc) {
                        camera::PinholeCameraParameters parameter;
                        vc.ConvertToPinholeCameraParameters(parameter);
                        return parameter;
                    },
                    "Function to convert visualization::ViewControl to "
                    "camera::PinholeCameraParameters")
            .def("convert_from_pinhole_camera_parameters",
                 &visualization::ViewControl::
                         ConvertFromPinholeCameraParameters,
                 "parameter"_a)
            .def("scale", &visualization::ViewControl::Scale,
                 "Function to process scaling", "scale"_a)
            .def("rotate", &visualization::ViewControl::Rotate,
                 "Function to process rotation", "x"_a, "y"_a, "xo"_a = 0.0,
                 "yo"_a = 0.0)
            .def("translate", &visualization::ViewControl::Translate,
                 "Function to process translation", "x"_a, "y"_a, "xo"_a = 0.0,
                 "yo"_a = 0.0)
            .def("get_field_of_view",
                 &visualization::ViewControl::GetFieldOfView,
                 "Function to get field of view")
            .def("change_field_of_view",
                 &visualization::ViewControl::ChangeFieldOfView,
                 "Function to change field of view", "step"_a = 0.45)
            .def("set_constant_z_near",
                 &visualization::ViewControl::SetConstantZNear,
                 "Function to change the near z-plane of the visualizer to a "
                 "constant value, i.e., independent of zoom and bounding box "
                 "size.",
                 "z_near"_a)
            .def("set_constant_z_far",
                 &visualization::ViewControl::SetConstantZFar,
                 "Function to change the far z-plane of the visualizer to a "
                 "constant value, i.e., independent of zoom and bounding box "
                 "size.",
                 "z_far"_a)
            .def("unset_constant_z_near",
                 &visualization::ViewControl::UnsetConstantZNear,
                 "Function to remove a previously set constant z near value, "
                 "i.e., near z-plane of the visualizer is dynamically set "
                 "dependent on zoom and bounding box size.")
            .def("unset_constant_z_far",
                 &visualization::ViewControl::UnsetConstantZFar,
                 "Function to remove a previously set constant z far value, "
                 "i.e., far z-plane of the visualizer is dynamically set "
                 "dependent on zoom and bounding box size.");
    docstring::ClassMethodDocInject(m, "ViewControl", "change_field_of_view",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl",
                                    "convert_from_pinhole_camera_parameters",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl",
                                    "convert_to_pinhole_camera_parameters",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "get_field_of_view",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "rotate",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "scale",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "translate",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "set_constant_z_near",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "set_constant_z_far",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "unset_constant_z_near",
                                    map_view_control_docstrings);
    docstring::ClassMethodDocInject(m, "ViewControl", "unset_constant_z_far",
                                    map_view_control_docstrings);
}

void pybind_viewcontrol_method(py::module &m) {}