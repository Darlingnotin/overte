#
#  Created by Anthony Thibault on 2015/12/18
#  Copyright 2015 High Fidelity, Inc.
#  Copyright 2023 Overte e.V.
#
#  Distributed under the Apache License, Version 2.0.
#  See the accompanying file LICENSE or http:#www.apache.org/licenses/LICENSE-2.0.html
#  SPDX-License-Identifier: Apache-2.0
#

if (WIN32)

    set(TARGET_NAME hifiNeuron)
    setup_hifi_plugin(Qml)
    link_hifi_libraries(shared controllers qml ui plugins input-plugins)
    include_hifi_library_headers(script-engine)
    target_neuron()

endif()
