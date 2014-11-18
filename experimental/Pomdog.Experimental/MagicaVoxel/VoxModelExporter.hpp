﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_VOXMODELEXPORTER_F3E3A4F5_F454_4E43_B1BB_BF0E9F237B54_HPP
#define POMDOG_VOXMODELEXPORTER_F3E3A4F5_F454_4E43_B1BB_BF0E9F237B54_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <string>

namespace Pomdog {
namespace Details {
namespace MagicaVoxel {

class VoxModel;

class VoxModelExporter {
public:
	static void Export(MagicaVoxel::VoxModel const& model, std::string const& filePath);
};

}// namespace MagicaVoxel
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_VOXMODELEXPORTER_F3E3A4F5_F454_4E43_B1BB_BF0E9F237B54_HPP)