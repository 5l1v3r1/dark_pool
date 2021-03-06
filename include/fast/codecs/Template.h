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
#ifndef TEMPLATE_H
#define TEMPLATE_H
#include "Template_fwd.h"
#include <Common/QuickFAST_Export.h>
#include <Common/Types.h>
#include <Codecs/SegmentBody.h>

namespace QuickFAST{
  namespace Codecs{
    /// @brief The internal representation of a FAST template.
    ///
    /// Defines the fields that will be sent for a message when this
    /// template is used.
    class QuickFAST_Export Template : public SegmentBody
    {
    public:
      /// @brief Construct an empty template.
      Template()
        : SegmentBody(1) // init pmap bit count to one for the templateID
        , templateId_(0)
        , reset_(false)
        , ignore_(false)
      {
      }

      /// @brief Destructor.
      virtual ~Template()
      {
      }

      /// @brief Set the templates identity
      /// @param id is the identifier for this template.
      void setId(template_id_t id)
      {
        templateId_ = id;
      }

      /// @brief Set the template name.
      /// Name is not as important as ID, but it is more human-friendly.
      /// @param name the name assigned to this template
      void setTemplateName(const std::string & name)
      {
        templateName_ = name;
      }

      /// @brief Set the template namespace.
      /// The namespace in which name is defined.
      /// @param templateNamespace the name assigned to this template
      void setTemplateNamespace(const std::string & templateNamespace)
      {
        templateNamespace_ = templateNamespace;
      }

      /// @brief Set the namespace for enclosed elements.
      /// The namespace for elements within this template
      /// @param templateNamespace for enclosed elements
      void setNamespace(const std::string & templateNamespace)
      {
        namespace_ = templateNamespace;
      }

      /// @brief Set the "reset-dictionaries-before-xcoding" flag
      ///
      /// @param reset true means reset, false means don't
      void setReset(bool reset)
      {
        reset_ = reset;
      }

      /// @brief Set the "ignore-this-message-after-decoding" flag
      /// @param ignore true means ignore, false means don't
      void setIgnore(bool ignore)
      {
        ignore_ = ignore;
      }

      /// @brief Retrieve the template id
      /// @returns the template id.
      template_id_t getId()const
      {
        return templateId_;
      }

      /// @brief Retrieve the template's name
      /// @returns the name of this template.
      const std::string & getTemplateName()const
      {
        return templateName_;
      }

      /// @brief Retrieve the namespace to qualify the template name
      const std::string & getTemplateNamespace()const
      {
        return namespace_;
      }

      /// @brief Retrieve the namespace to qualify names of enclosed elements.
      const std::string & getNamespace()const
      {
        return namespace_;
      }

      /// @brief should the dictionaries be reset for this template?
      /// @returns true if they should be reset.
      bool getReset()const
      {
        return reset_;
      }

      /// @brief should the messages decoded by this template be ignored?
      /// @returns true if they should be ignored.
      bool getIgnore()const
      {
        return ignore_;
      }

      /// @brief use the namespace to qualify the local name
      /// @param out receives the qualified name
      void qualifyName(std::string &out)const
      {
        qualifyName(out, templateName_, templateNamespace_);
      }

      /// @brief use a namespace to qualify the local name
      /// @param[out] out receives the qualified name
      /// @param[in] templateName is the local name of the template
      /// @param[in] templateNamespace qualifies local name
      static void qualifyName(
        std::string & out,
        const std::string & templateName,
        const std::string &templateNamespace);

      /// @brief Write the template in human readable form.
      ///
      /// @param output is the stream to which the display will be written
      /// @param indent is the number of spaces to appear at the beginning of each line.
      void display(std::ostream & output, size_t indent = 0) const;

    private:
      uint32 templateId_;
      std::string templateName_;
      std::string templateNamespace_;
      std::string namespace_;
      bool reset_; // if true reset dictionaries before Xcoding this template
      bool ignore_; // if true ignore the results of decoding this message.
    };
  }
}
#endif // TEMPLATE_H
