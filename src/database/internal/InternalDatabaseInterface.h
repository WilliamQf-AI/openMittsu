#ifndef OPENMITTSU_DATABASE_INTERNAL_INTERNALDATABASEINTERFACE_H_
#define OPENMITTSU_DATABASE_INTERNAL_INTERNALDATABASEINTERFACE_H_

#include <QString>
#include <QSqlQuery>
#include <QSqlError>

#include "src/protocol/ContactId.h"
#include "src/protocol/GroupId.h"
#include "src/protocol/MessageId.h"

#include "src/database/MediaFileType.h"

namespace openmittsu {
	namespace database {
		class MediaFileItem;

		namespace internal {

			class InternalDatabaseInterface {
			public:
				virtual ~InternalDatabaseInterface() {}

				virtual openmittsu::protocol::ContactId getSelfContact() const = 0;
				virtual QString generateUuid() const = 0;

				// Queries
				virtual QSqlQuery getQueryObject() const = 0;
				virtual bool transactionStart() = 0;
				virtual bool transactionCommit() = 0;

				// Announces
				virtual void announceMessageChanged(QString const& uuid) = 0;
				virtual void announceMessageDeleted(QString const& uuid) = 0;
				virtual void announceContactChanged(openmittsu::protocol::ContactId const& contact) = 0;
				virtual void announceGroupChanged(openmittsu::protocol::GroupId const& group) = 0;
				virtual void announceNewMessage(openmittsu::protocol::ContactId const& contact, QString const& messageUuid) = 0;
				virtual void announceNewMessage(openmittsu::protocol::GroupId const& group, QString const& messageUuid) = 0;
				virtual void announceReceivedNewMessage(openmittsu::protocol::ContactId const& contact) = 0;
				virtual void announceReceivedNewMessage(openmittsu::protocol::GroupId const& group) = 0;

				// Message ID
				virtual openmittsu::protocol::MessageId getNextMessageId(openmittsu::protocol::ContactId const& contact) = 0;
				virtual openmittsu::protocol::MessageId getNextMessageId(openmittsu::protocol::GroupId const& group) = 0;

				// Media Items
				virtual MediaFileItem getMediaItem(QString const& uuid, MediaFileType const& fileType) const = 0;
				virtual void removeMediaItem(QString const& uuid, MediaFileType const& fileType) = 0;
				virtual void removeAllMediaItems(QString const& uuid) = 0;
				// Returns false iff the UUID already exists.
				virtual bool insertMediaItem(QString const& uuid, QByteArray const& data, MediaFileType const& fileType) = 0;
			};

		}
	}
}

#endif // OPENMITTSU_DATABASE_INTERNAL_INTERNALDATABASEINTERFACE_H_
