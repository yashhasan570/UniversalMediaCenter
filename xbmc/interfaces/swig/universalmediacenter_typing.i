/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

// PEP 484 annotations for the -pyi stub files; pytyping typemaps shape stub text only, never wrapper code
%feature("python:annotations", "typing");

// names only: autodoc's typed modes emit C++ types, not python
%feature("autodoc", "0");

// wrapped objects annotate as their proxy class instead of the typing.Any catch-all
%typemap(pytyping) SWIGTYPE * "$pytypename"
%typemap(pytyping) SWIGTYPE & "$pytypename"

// one annotation per API shape, all passing spellings at once
%define UNIVERSAL MEDIA CENTER_PYTYPE(TYPE, ANN)
%typemap(pytyping) TYPE, const TYPE &, TYPE *, const TYPE * ANN
%enddef

UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<std::string>), "typing.List[str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<int>), "typing.List[int]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<bool>), "typing.List[bool]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<double>), "typing.List[float]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::::Actor*>), "typing.List[Actor]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::::Actor const*>), "typing.List[Actor]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::::ContentGeometrySection*>), "typing.List[ContentGeometrySection]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::gui::ListItem*>), "typing.List[ListItem]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::gui::ListItem const*>), "typing.List[ListItem]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::gui::Control*>), "typing.List[Control]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::map<std::string, std::string>), "typing.Dict[str, str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::map<std::string, std::string, std::less<> >), "typing.Dict[str, str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::map<std::string, Addon::Tuple<float, int> >), "typing.Dict[str, typing.Tuple[float, int]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Dictionary<std::string>), "typing.Dict[str, str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Dictionary<std::string> >), "typing.List[typing.Dict[str, str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Tuple<std::string, std::string>), "typing.Tuple[str, str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Tuple<float, int>), "typing.Tuple[float, int]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Tuple<int, std::string, std::string>), "typing.Tuple[int, str, str]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Tuple<std::string, Addon::gui::ListItem const*, bool>), "typing.Tuple[str, ListItem, bool]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Tuple<std::vector<std::string>, std::vector<std::string> >), "typing.Tuple[typing.List[str], typing.List[str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Tuple<std::string, std::string> >), "typing.List[typing.Tuple[str, str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Tuple<int, std::string, std::string> >), "typing.List[typing.Tuple[int, str, str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Tuple<std::string, Addon::gui::ListItem const*, bool> >), "typing.List[typing.Tuple[str, ListItem, bool]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Alternative<std::string, Addon::gui::ListItem const*>), "typing.Union[str, ListItem]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Alternative<std::string, std::vector<std::string> >), "typing.Union[str, typing.List[str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Alternative<std::string, Addon::::PlayList const*>), "typing.Union[str, PlayList]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> >), "typing.Union[str, typing.Tuple[str, str]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > >), "typing.List[typing.Union[str, typing.Tuple[str, str]]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::vector<Addon::Alternative<std::string, Addon::gui::ListItem const*> >), "typing.List[typing.Union[str, ListItem]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Alternative<std::string, std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > > >), "typing.Union[str, typing.List[typing.Union[str, typing.Tuple[str, str]]]]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(Addon::Dictionary<Addon::Alternative<std::string, std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > > > >), "typing.Dict[str, typing.Any]")
UNIVERSAL MEDIA CENTER_PYTYPE(%arg(std::unique_ptr<std::vector<int> >), "typing.Optional[typing.List[int]]")
%typemap(pytyping) int64_t, long long "int"

// classes referenced across modules have no local proxy for $pytypename to name
UNIVERSAL MEDIA CENTER_PYTYPE(Addon::gui::ListItem, "ListItem")
UNIVERSAL MEDIA CENTER_PYTYPE(Addon::::InfoTagVideo, "InfoTagVideo")
UNIVERSAL MEDIA CENTER_PYTYPE(Addon::::InfoTagMusic, "InfoTagMusic")
UNIVERSAL MEDIA CENTER_PYTYPE(Addon::::InfoTagPicture, "InfoTagPicture")
UNIVERSAL MEDIA CENTER_PYTYPE(Addon::::InfoTagGame, "InfoTagGame")

%typemap(pytyping) const Addon::gui::ListItemList * "typing.List[ListItem]"
%typemap(pytyping, out="bytearray") XbmcCommons::Buffer, XbmcCommons::Buffer &, const XbmcCommons::Buffer &, XbmcCommons::Buffer *, const XbmcCommons::Buffer * "typing.Union[str, bytes, bytearray]"
%typemap(pytyping) PyObject * "typing.Any"
%typemap(pytyping) void * "typing.Any"
