#include "src/protocol/TextLengthLimiter.h"

namespace openmittsu {
	namespace protocol {

		QStringList TextLengthLimiter::splitTextForSending(QString const& text) {
			int const maxLengthInBytes = PROTO_MESSAGE_CONTENT_PAYLOAD_MAX_LENGTH_BYTES;

			if (text.toUtf8().size() <= maxLengthInBytes) {
				return { text };
			} else {
				QStringList result;

				int startPosition = 0;
				while (true) {
					int currentLength = maxLengthInBytes;

					// Check if the remainder fits
					if (text.mid(startPosition).toUtf8().size() <= maxLengthInBytes) {
						result.append(text.mid(startPosition));
						break;
					}

					QString currentSubstring = text.mid(startPosition, maxLengthInBytes);
					while (currentSubstring.toUtf8().size() > maxLengthInBytes) {
						--currentLength;
						currentSubstring = text.mid(startPosition, currentLength);
					}

					int const splitPositionSpace = currentSubstring.lastIndexOf(' ');
					int const splitPositionNewLineA = currentSubstring.lastIndexOf('\r');
					int const splitPositionNewLineB = currentSubstring.lastIndexOf('\n');
					int const splitPositionTab = currentSubstring.lastIndexOf('\t');

					int splitPosition = std::max(std::max(splitPositionSpace, std::min(splitPositionNewLineA, splitPositionNewLineB)), splitPositionTab);

					// -1: failed, 0: first character. Does not help when splitting.
					if (splitPosition <= 0) {
						result.append(currentSubstring);
						startPosition += currentLength;
					} else {
						++splitPosition;
						currentLength = splitPosition - startPosition;
						currentSubstring = text.mid(startPosition, currentLength);
						result.append(currentSubstring);
						startPosition = splitPosition;
					}
				}

				return result;
			}
		}

		int TextLengthLimiter::getMaximumTextLength() {
			return PROTO_MESSAGE_CONTENT_PAYLOAD_MAX_LENGTH_BYTES;
		}

	}
}
