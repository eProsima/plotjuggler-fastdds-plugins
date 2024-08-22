// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Visualizer Plugin.
//
// eProsima Fast DDS Visualizer Plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Visualizer Plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Visualizer Plugin. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file Participant.hpp
 */

#ifndef _EPROSIMA_PLOTJUGGLERFASTDDSPLUGIN_PLUGINS_DATASTREAMERPLUGIN_FASTDDS_PARTICIPANTS_HPP_
#define _EPROSIMA_PLOTJUGGLERFASTDDSPLUGIN_PLUGINS_DATASTREAMERPLUGIN_FASTDDS_PARTICIPANTS_HPP_

#include <functional>
#include <memory>
#include <unordered_map>
#include <QObject>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/xtypes/type_representation/detail/dds_xtypes_typeobject.hpp>

#include <fastdds/rtps/writer/WriterDiscoveryStatus.hpp>
#include <fastdds/rtps/builtin/data/PublicationBuiltinTopicData.hpp>

#include "FastDdsListener.hpp"
#include "ReaderHandler.hpp"
#include "TopicDataBase.hpp"

namespace eprosima {
namespace plotjuggler {
namespace fastdds {

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
class ReaderHandlerDeleter
{
public:

    ReaderHandlerDeleter(
            DomainParticipant* participant,
            Subscriber* subscriber);

    void operator ()(
            ReaderHandler* ptr) const;

protected:

    DomainParticipant* participant_;
    Subscriber* subscriber_;
};

using ReaderHandlerReference = std::unique_ptr<ReaderHandler, ReaderHandlerDeleter>;

/**
 * @brief This class handles every Fast DDS entity required.
 *
 * It create, manage and destroy every Fast DDS entity that the process requires to instantiate.
 * The discovery and user data received is transmitted through a FastDdsListener object.
 *
 * FUTURE WORK:
 * Use a specific thread to call callbacks instead of using Fast DDS thread
 */
class Participant : public DomainParticipantListener
{
public:

    ////////////////////////////////////////////////////
    // CREATION & DESTRUCTION
    ////////////////////////////////////////////////////

    Participant(
            DomainId_t domain_id,
            std::shared_ptr<TopicDataBase> discovery_database,
            FastDdsListener* listener);

    virtual ~Participant();


    ////////////////////////////////////////////////////
    // INTERACTION METHODS
    ////////////////////////////////////////////////////

//     bool register_type_from_xml(
//             const std::string& xml_path);

    void create_subscription(
            const std::string& topic_name,
            const DataTypeConfiguration& data_type_configuration);


    ////////////////////////////////////////////////////
    // LISTENER [ DOMAIN PARTICIPANT ] METHODS
    ////////////////////////////////////////////////////

    void on_data_writer_discovery(
            DomainParticipant* participant,
            WriterDiscoveryStatus reason,
            const PublicationBuiltinTopicData& info,
            bool& should_be_ignored) override;

    ////////////////////////////////////////////////////
    // RETRIEVE INFORMATION METHODS
    ////////////////////////////////////////////////////

    std::vector<types::DatumLabel> numeric_data_series_names() const;

    std::vector<types::DatumLabel> string_data_series_names() const;

protected:

    ////////////////////////////////////////////////////
    // EXTERNAL EVENT METHODS
    ////////////////////////////////////////////////////

    void on_topic_discovery_(
            const std::string& topic_name,
            const std::string& type_name,
            const DataTypeId& type_id);

    ////////////////////////////////////////////////////
    // AUXILIAR STATIC METHODS
    ////////////////////////////////////////////////////

    static DomainParticipantQos default_participant_qos_();

    static SubscriberQos default_subscriber_qos_();

    static TopicQos default_topic_qos_();

    static DataReaderQos default_datareader_qos_();

    /**
     * @brief Get default mask
     *
     * Callbacks accepted by this mask:
     * - Every DomainParticipantListener callback (cannot be disabled)
     *
     * @note it is important to have a mask, otherwise onDataOnReaders would hide on_data_available
     *
     * @return eprosima::fastdds::dds::StatusMask with callbacks needed
     */
    static StatusMask default_listener_mask_();


    ////////////////////////////////////////////////////
    // INTERNAL VARIABLES
    ////////////////////////////////////////////////////

    std::shared_ptr<TopicDataBase> discovery_database_;

    FastDdsListener* listener_;


    ////////////////////////////////////////////////////
    // FAST DDS POINTERS
    ////////////////////////////////////////////////////

    //! Internal DomainParticipant reference
    DomainParticipant* participant_;
    //! Internal Subscriber reference (only one for every DataReader)
    Subscriber* subscriber_;

    /**
     * Collection created in Participant indexed by topic name that contains
     * Reader, Topic and DataType so messages read is disengaged from this object
     */
    std::unordered_map<std::string, ReaderHandlerReference> readers_;

};

} /* namespace fastdds */
} /* namespace plotjuggler */
} /* namespace eprosima */

#endif // _EPROSIMA_PLOTJUGGLERFASTDDSPLUGIN_PLUGINS_DATASTREAMERPLUGIN_FASTDDS_PARTICIPANTS_HPP_
