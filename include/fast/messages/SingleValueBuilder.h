// Copyright (c) 2009, 2010, 2011 Object Computing, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//    * Neither the name of Object Computing, Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from this
//      software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifdef _MSC_VER
# pragma once
#endif
#ifndef SINGLEVALUEBUILDER_H
#define SINGLEVALUEBUILDER_H
#include <Messages/ValueMessageBuilder.h>
#include <Common/Value.h>

namespace QuickFAST
{
  namespace Messages
  {
    ///@brief a MessageBuilder that creates a "record" containing a single value
    ///
    /// Or more accurately, captures a single value produced by the decoder.
    template<typename DATATYPE>
    class SingleValueBuilder : public ValueMessageBuilder
    {
      public:
        SingleValueBuilder();
        virtual ~SingleValueBuilder();

        ///////////////////////////
        // Implement ValueMessageBuilder
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int64 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint64 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int32 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint32 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int16 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint16 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int8 value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uchar value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const Decimal& value);
        virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const unsigned char * value, size_t length);
        virtual ValueMessageBuilder & startMessage(
          const std::string & applicationType,
          const std::string & applicationTypeNamespace,
          size_t size);
        virtual bool endMessage(ValueMessageBuilder & messageBuilder);
        virtual bool ignoreMessage(ValueMessageBuilder & messageBuilder);

        /// @brief check to see if a value was set
        ///
        /// @returns true if a value was set
        bool isSet()const;

        /// @brief retrieve the captured value
        ///
        /// probably a good idea to check isSet() first
        /// @returns the value
        DATATYPE value()const;

        /// @brief access the identity that was used to set the value
        FieldIdentityCPtr & identity()const;

        /// @brief clear flag used by isSet()
        void reset();

      private:
        /////////////////////////////////////////////////
        // Dummy implementations of other virtual methods
        virtual void clear(size_t /*capacity*/){}
        virtual void reserve(size_t /*capacity*/){}
        virtual size_t size() const
        {
          return 1;
        }

        virtual bool getIdentity(const std::string &/*name*/, FieldIdentityCPtr & identity) const
        {
          identity = identity_;
          return bool(identity);
        }

        virtual void setApplicationType(const std::string & /*type*/, const std::string & /*ns*/)
        {
        }

        virtual const std::string & getApplicationType() const
        {
          static const std::string name("singlevalue");
          return name;
        }

        virtual const std::string & getApplicationTypeNs() const
        {
          static const std::string result("");
          return result;
        }

        virtual ValueMessageBuilder & startSequence(
          FieldIdentityCPtr & identity,
          const std::string & applicationType,
          const std::string & applicationTypeNamespace,
          size_t fieldCount,
          FieldIdentityCPtr & lengthIdentity,
          size_t length)
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support start sequence.");
        }

        virtual ValueMessageBuilder & startSequenceEntry(
          const std::string & /*applicationType*/,
          const std::string & /*applicationTypeNamespace*/,
          size_t /*size*/)
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support start sequence entry.");
        }

        virtual void endSequenceEntry(ValueMessageBuilder & /*entry*/)
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support end sequence entry.");
        }
        virtual void endSequence(FieldIdentityCPtr & /*identity*/, ValueMessageBuilder & )
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support end sequence.");
        }

        virtual ValueMessageBuilder & startGroup(
          FieldIdentityCPtr & /*identity*/,
          const std::string & /*applicationType*/,
          const std::string & /*applicationTypeNamespace*/,
          size_t /*size*/)
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support start group.");
        }

        virtual void endGroup(
          FieldIdentityCPtr & /*identity*/,
          ValueMessageBuilder & /*entry*/)
        {
          throw UsageError("Coding Error", "SingleValueBuilder does not support end group.");
        }

        virtual bool wantLog(unsigned short /*level*/)
        {
          return false;
        }

        virtual bool logMessage(unsigned short /*level*/, const std::string & /*logMessage*/)
        {
          return true;
        }

        virtual bool reportDecodingError(const std::string & /*errorMessage*/)
        {
          return true;
        }

        virtual bool reportCommunicationError(const std::string & /*errorMessage*/)
        {
          return true;
        }

      private:
        Value value_;
        mutable FieldIdentityCPtr identity_;
    };

    template<typename DATATYPE>
    inline
    SingleValueBuilder<DATATYPE>::SingleValueBuilder()
    {
    }

    template<typename DATATYPE>
    inline
    SingleValueBuilder<DATATYPE>::~SingleValueBuilder()
    {
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int64 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint64 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int32 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint32 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int16 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint16 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int8 value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uchar value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const Decimal& value)
    {
      identity_ = identity;
      value_.setValue(value);
    }

    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::addValue(FieldIdentityCPtr & identity, ValueType::Type type, const unsigned char * value, size_t length)
    {
      identity_ = identity;
      value_.setValue(value, length);
    }

    template<typename DATATYPE>
    inline ValueMessageBuilder &
    SingleValueBuilder<DATATYPE>::startMessage(
      const std::string & /*applicationType*/,
      const std::string & /*applicationTypeNamespace*/,
      size_t /*size*/)
    {
      return *this;
    }

    template<typename DATATYPE>
    inline bool
    SingleValueBuilder<DATATYPE>::endMessage(ValueMessageBuilder & messageBuilder)
    {
      return true;
    }

    template<typename DATATYPE>
    inline bool
    SingleValueBuilder<DATATYPE>::ignoreMessage(ValueMessageBuilder & messageBuilder)
    {
      value_.setNull();
      return true;
    }

    template<typename DATATYPE>
    inline bool
    SingleValueBuilder<DATATYPE>::isSet()const
    {
      return value_.isDefined();
    }
    template<typename DATATYPE>
    inline void
    SingleValueBuilder<DATATYPE>::reset()
    {
      value_.setUndefined();
    }


    template<typename DATATYPE>
    inline DATATYPE
    SingleValueBuilder<DATATYPE>::value()const
    {
      DATATYPE result = DATATYPE();
      value_.getValue(result);
      return result;
    }

    template<typename DATATYPE>
    inline FieldIdentityCPtr &
    SingleValueBuilder<DATATYPE>::identity()const
    {
      return identity_;
    }
  }
}

#endif // SINGLEVALUEBUILDER_H

