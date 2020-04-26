#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Eigen/Core>
#include "BaseTypes/Node.hpp"
#include "BaseTypes/Mesh.hpp"
#include "BaseTypes/Tree.hpp"
#include "BaseTypes/GrowthInfo.hpp"
#include "TreeFunctions/TrunkFunction.hpp"
#include "TreeFunctions/BranchFunction.hpp"
#include "TreeFunctions/GrowthFunction.hpp"
#include "Meshers/BasicMesher.hpp"

using namespace Mtree;

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;


PYBIND11_MODULE(m_tree, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<TreeFunction, std::shared_ptr<TreeFunction>>(m, "TreeFunction")
        .def("add_child", &TreeFunction::add_child);

    py::class_<TrunkFunction, std::shared_ptr<TrunkFunction>, TreeFunction>(m, "TrunkFunction")
        .def(py::init<>())
        .def_readwrite("length", &TrunkFunction::length)
        .def_readwrite("resolution", &TrunkFunction::resolution)
        .def_readwrite("radius", &TrunkFunction::radius)
        .def_readwrite("randomness", &TrunkFunction::randomness)
        ;
    
    py::class_<BranchFunction, std::shared_ptr<BranchFunction>, TreeFunction>(m, "BranchFunction")
        .def(py::init<>())
        .def_readwrite("length", &BranchFunction::length)
        .def_readwrite("resolution", &BranchFunction::resolution)
        .def_readwrite("radius", &BranchFunction::radius)
        .def_readwrite("randomness", &BranchFunction::randomness)
        .def_readwrite("branches_per_meter", &BranchFunction::branches_per_meter)
        .def_readwrite("split_radius", &BranchFunction::split_radius)
        .def_readwrite("branch_angle", &BranchFunction::branch_angle)
        .def_readwrite("split_angle", &BranchFunction::split_angle)
        .def_readwrite("split_proba", &BranchFunction::split_proba)
        ;

    py::class_<GrowthFunction, std::shared_ptr<GrowthFunction>, TreeFunction>(m, "GrowthFunction")
        .def(py::init<>())
        .def_readwrite("iterations", &GrowthFunction::iterations)
        .def_readwrite("apical_dominance", &GrowthFunction::apical_dominance)
        .def_readwrite("grow_threshold", &GrowthFunction::grow_threshold)
        .def_readwrite("cut_threshold", &GrowthFunction::cut_threshold)
        .def_readwrite("split_threshold", &GrowthFunction::split_threshold)
        .def_readwrite("split_angle", &GrowthFunction::split_angle)
        .def_readwrite("branch_length", &GrowthFunction::branch_length)
        .def_readwrite("gravitropism", &GrowthFunction::gravitropism)
        .def_readwrite("randomness", &GrowthFunction::randomness)
        .def_readwrite("gravity_strength", &GrowthFunction::gravity_strength)
        ;


    py::class_<Tree>(m, "Tree")
        .def(py::init<>())
        .def("set_trunk_function", &Tree::set_first_function)
        .def("get_trunk_function", &Tree::get_first_function)
        .def("execute_functions", &Tree::execute_functions);

    py::class_<Mesh>(m, "Mesh")
        .def("get_vertices", &Mesh::get_vertices)
        .def("get_polygons", &Mesh::get_polygons);

    py::class_<TreeMesher>(m, "TreeMesher");

    py::class_<BasicMesher>(m, "BasicMesher")
        .def(py::init<>())
        .def("mesh_tree", &BasicMesher::mesh_tree);


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}