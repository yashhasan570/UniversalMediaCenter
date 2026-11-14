/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "XBDateTime.h"
#include "utils/StringUtils.h"
#include "utils/TinyXML.h"
#include "utils/TinyXML2.h"
#include "utils/XMLUtils.h"

#include <gtest/gtest.h>

TEST(TestXMLUtils, GetUInt)
{
  CTinyXML a;
  uint32_t ref, val, val2;

  a.Parse(std::string("<root><node>1000</node></root>"));
  EXPECT_TRUE(XMLUtils::GetUInt(a.RootElement(), "node", val));

  ref = 1000;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>1000</node></root>"));
  EXPECT_TRUE(XMLUtils::GetUInt(b.RootElement(), "node", val2));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, GetFloat)
{
  CTinyXML a;
  float ref, val, val2;

  a.Parse(std::string("<root><node>1000.1f</node></root>"));
  EXPECT_TRUE(XMLUtils::GetFloat(a.RootElement(), "node", val));
  EXPECT_TRUE(XMLUtils::GetFloat(a.RootElement(), "node", val, 1000.0f,
                                 1000.2f));
  ref = 1000.1f;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>1000.1f</node></root>"));
  EXPECT_TRUE(XMLUtils::GetFloat(b.RootElement(), "node", val2));
  EXPECT_TRUE(XMLUtils::GetFloat(b.RootElement(), "node", val2, 1000.0f, 1000.2f));

  EXPECT_EQ(ref, val);
}

TEST(TestXMLUtils, GetDouble)
{
  CTinyXML a;
  double val, val2;
  std::string refstr, valstr, valstr2;

  a.Parse(std::string("<root><node>1000.1f</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDouble(a.RootElement(), "node", val));

  refstr = "1000.100000";
  valstr = StringUtils::Format("{:f}", val);
  EXPECT_STREQ(refstr.c_str(), valstr.c_str());

  CTinyXML2 b;

  b.Parse(std::string("<root><node>1000.1f</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDouble(b.RootElement(), "node", val2));

  valstr2 = StringUtils::Format("{:f}", val2);
  EXPECT_STREQ(refstr.c_str(), valstr2.c_str());
}

TEST(TestXMLUtils, GetInt)
{
  CTinyXML a;
  int ref, val, val2;

  a.Parse(std::string("<root><node>1000</node></root>"));
  EXPECT_TRUE(XMLUtils::GetInt(a.RootElement(), "node", val));
  EXPECT_TRUE(XMLUtils::GetInt(a.RootElement(), "node", val, 999, 1001));

  ref = 1000;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>1000</node></root>"));
  EXPECT_TRUE(XMLUtils::GetInt(b.RootElement(), "node", val2));
  EXPECT_TRUE(XMLUtils::GetInt(b.RootElement(), "node", val2, 999, 1001));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, GetBoolean)
{
  CTinyXML a;
  bool ref, val, val2;

  a.Parse(std::string("<root><node>true</node></root>"));
  EXPECT_TRUE(XMLUtils::GetBoolean(a.RootElement(), "node", val));

  ref = true;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>true</node></root>"));
  EXPECT_TRUE(XMLUtils::GetBoolean(b.RootElement(), "node", val2));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, GetString)
{
  CTinyXML a;
  std::string ref, val, val2;

  a.Parse(std::string("<root><node>some string</node></root>"));
  EXPECT_TRUE(XMLUtils::GetString(a.RootElement(), "node", val));

  ref = "some string";
  EXPECT_STREQ(ref.c_str(), val.c_str());

  CTinyXML2 b;

  b.Parse(std::string("<root><node>some string</node></root>"));
  EXPECT_TRUE(XMLUtils::GetString(b.RootElement(), "node", val2));

  EXPECT_STREQ(ref.c_str(), val2.c_str());
}

TEST(TestXMLUtils, GetStringArray)
{
  CTinyXML a;
  std::vector<std::string> strarray, strarray2;

  a.Parse(std::string("<root>\n"
          "  <node>some string1</node>\n"
          "  <node>some string2</node>\n"
          "  <node>some string3</node>\n"
          "  <node>some string4</node>\n"
          "  <node>some string5</node>\n"
          "</root>\n"));
  EXPECT_TRUE(XMLUtils::GetStringArray(a.RootElement(), "node", strarray));

  EXPECT_STREQ("some string1", strarray.at(0).c_str());
  EXPECT_STREQ("some string2", strarray.at(1).c_str());
  EXPECT_STREQ("some string3", strarray.at(2).c_str());
  EXPECT_STREQ("some string4", strarray.at(3).c_str());
  EXPECT_STREQ("some string5", strarray.at(4).c_str());

  CTinyXML2 b;

  b.Parse(std::string("<root>\n"
                      "  <node>some string1</node>\n"
                      "  <node>some string2</node>\n"
                      "  <node>some string3</node>\n"
                      "  <node>some string4</node>\n"
                      "  <node>some string5</node>\n"
                      "</root>\n"));
  EXPECT_TRUE(XMLUtils::GetStringArray(b.RootElement(), "node", strarray2));

  EXPECT_STREQ("some string1", strarray2.at(0).c_str());
  EXPECT_STREQ("some string2", strarray2.at(1).c_str());
  EXPECT_STREQ("some string3", strarray2.at(2).c_str());
  EXPECT_STREQ("some string4", strarray2.at(3).c_str());
  EXPECT_STREQ("some string5", strarray2.at(4).c_str());
}

TEST(TestXMLUtils, GetPath)
{
  CTinyXML a, b;
  std::string ref, val, val2;

  a.Parse(std::string("<root><node urlencoded=\"yes\">special:///</node></root>"));
  EXPECT_TRUE(XMLUtils::GetPath(a.RootElement(), "node", val));

  ref = "special:///";
  EXPECT_STREQ(ref.c_str(), val.c_str());

  val.clear();
  b.Parse(std::string("<root><node>special://bin/</node></root>"));
  EXPECT_TRUE(XMLUtils::GetPath(b.RootElement(), "node", val));

  ref = "special://bin/";
  EXPECT_STREQ(ref.c_str(), val.c_str());

  CTinyXML2 c, d;

  c.Parse(std::string("<root><node urlencoded=\"yes\">special:///</node></root>"));
  EXPECT_TRUE(XMLUtils::GetPath(c.RootElement(), "node", val2));

  ref = "special:///";
  EXPECT_STREQ(ref.c_str(), val2.c_str());

  val2.clear();
  d.Parse(std::string("<root><node>special://bin/</node></root>"));
  EXPECT_TRUE(XMLUtils::GetPath(d.RootElement(), "node", val2));

  ref = "special://bin/";
  EXPECT_STREQ(ref.c_str(), val2.c_str());
}

TEST(TestXMLUtils, GetDate)
{
  CTinyXML a;
  CDateTime ref, val, val2;

  a.Parse(std::string("<root><node>2012-07-08</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDate(a.RootElement(), "node", val));
  ref.SetDate(2012, 7, 8);
  EXPECT_TRUE(ref == val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>2012-07-08</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDate(b.RootElement(), "node", val2));
  EXPECT_TRUE(ref == val2);
}

TEST(TestXMLUtils, GetDateTime)
{
  CTinyXML a;
  CDateTime ref, val, val2;

  a.Parse(std::string("<root><node>2012-07-08 01:02:03</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDateTime(a.RootElement(), "node", val));
  ref.SetDateTime(2012, 7, 8, 1, 2, 3);
  EXPECT_TRUE(ref == val);

  CTinyXML2 b;

  b.Parse(std::string("<root><node>2012-07-08 01:02:03</node></root>"));
  EXPECT_TRUE(XMLUtils::GetDateTime(b.RootElement(), "node", val2));
  EXPECT_TRUE(ref == val2);
}

TEST(TestXMLUtils, SetString)
{
  CTinyXML a;
  std::string ref, val, val2;

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetString(a.RootElement(), "node", "some string");
  EXPECT_TRUE(XMLUtils::GetString(a.RootElement(), "node", val));

  ref = "some string";
  EXPECT_STREQ(ref.c_str(), val.c_str());

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetString(b.RootElement(), "node", "some string");
  EXPECT_TRUE(XMLUtils::GetString(b.RootElement(), "node", val2));

  EXPECT_STREQ(ref.c_str(), val2.c_str());
}

TEST(TestXMLUtils, SetStringArray)
{
  CTinyXML a;
  std::vector<std::string> strarray;
  strarray.emplace_back("some string1");
  strarray.emplace_back("some string2");
  strarray.emplace_back("some string3");
  strarray.emplace_back("some string4");
  strarray.emplace_back("some string5");

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetStringArray(a.RootElement(), "node", strarray);
  EXPECT_TRUE(XMLUtils::GetStringArray(a.RootElement(), "node", strarray));

  EXPECT_STREQ("some string1", strarray.at(0).c_str());
  EXPECT_STREQ("some string2", strarray.at(1).c_str());
  EXPECT_STREQ("some string3", strarray.at(2).c_str());
  EXPECT_STREQ("some string4", strarray.at(3).c_str());
  EXPECT_STREQ("some string5", strarray.at(4).c_str());

  CTinyXML2 b;

  strarray.clear();
  strarray.emplace_back("some string1");
  strarray.emplace_back("some string2");
  strarray.emplace_back("some string3");
  strarray.emplace_back("some string4");
  strarray.emplace_back("some string5");

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetStringArray(b.RootElement(), "node", strarray);
  EXPECT_TRUE(XMLUtils::GetStringArray(b.RootElement(), "node", strarray));

  EXPECT_STREQ("some string1", strarray.at(0).c_str());
  EXPECT_STREQ("some string2", strarray.at(1).c_str());
  EXPECT_STREQ("some string3", strarray.at(2).c_str());
  EXPECT_STREQ("some string4", strarray.at(3).c_str());
  EXPECT_STREQ("some string5", strarray.at(4).c_str());
}

TEST(TestXMLUtils, SetInt)
{
  CTinyXML a;
  int ref, val, val2;

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetInt(a.RootElement(), "node", 1000);
  EXPECT_TRUE(XMLUtils::GetInt(a.RootElement(), "node", val));

  ref = 1000;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetInt(b.RootElement(), "node", 1000);
  EXPECT_TRUE(XMLUtils::GetInt(b.RootElement(), "node", val2));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, SetFloat)
{
  CTinyXML a;
  float ref, val, val2;

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetFloat(a.RootElement(), "node", 1000.1f);
  EXPECT_TRUE(XMLUtils::GetFloat(a.RootElement(), "node", val));

  ref = 1000.1f;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetFloat(b.RootElement(), "node", 1000.1f);
  EXPECT_TRUE(XMLUtils::GetFloat(b.RootElement(), "node", val2));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, SetBoolean)
{
  CTinyXML a;
  bool ref, val, val2;

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetBoolean(a.RootElement(), "node", true);
  EXPECT_TRUE(XMLUtils::GetBoolean(a.RootElement(), "node", val));

  ref = true;
  EXPECT_EQ(ref, val);

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetBoolean(b.RootElement(), "node", true);
  EXPECT_TRUE(XMLUtils::GetBoolean(b.RootElement(), "node", val2));

  EXPECT_EQ(ref, val2);
}

TEST(TestXMLUtils, SetPath)
{
  CTinyXML a;
  std::string ref, val, val2;

  a.Parse(std::string("<root></root>"));
  XMLUtils::SetPath(a.RootElement(), "node", "special:///");
  EXPECT_TRUE(XMLUtils::GetPath(a.RootElement(), "node", val));

  ref = "special:///";
  EXPECT_STREQ(ref.c_str(), val.c_str());

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetPath(b.RootElement(), "node", "special:///");
  EXPECT_TRUE(XMLUtils::GetPath(b.RootElement(), "node", val2));

  EXPECT_STREQ(ref.c_str(), val2.c_str());
}

TEST(TestXMLUtils, SetDate)
{
  CTinyXML a;
  CDateTime ref, val, val2;

  a.Parse(std::string("<root></root>"));
  ref.SetDate(2012, 7, 8);
  XMLUtils::SetDate(a.RootElement(), "node", ref);
  EXPECT_TRUE(XMLUtils::GetDate(a.RootElement(), "node", val));
  EXPECT_TRUE(ref == val);

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetDate(b.RootElement(), "node", ref);
  EXPECT_TRUE(XMLUtils::GetDate(b.RootElement(), "node", val2));
  EXPECT_TRUE(ref == val);
}

TEST(TestXMLUtils, SetDateTime)
{
  CTinyXML a;
  CDateTime ref, val, val2;

  a.Parse(std::string("<root></root>"));
  ref.SetDateTime(2012, 7, 8, 1, 2, 3);
  XMLUtils::SetDateTime(a.RootElement(), "node", ref);
  EXPECT_TRUE(XMLUtils::GetDateTime(a.RootElement(), "node", val));
  EXPECT_TRUE(ref == val);

  CTinyXML2 b;

  b.Parse(std::string("<root></root>"));
  XMLUtils::SetDateTime(b.RootElement(), "node", ref);
  EXPECT_TRUE(XMLUtils::GetDateTime(b.RootElement(), "node", val2));
  EXPECT_TRUE(ref == val2);
}

TEST(TestXMLUtils, NodeSerializationRoot)
{
  const std::string XmlDocument = "<root><node>some string</node></root>";
  const std::string expected = "<root><node>some string</node></root>";

  {
    // 1 - the node belongs to a document
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));

    // 2 - the node is not attached to a document
    TiXmlNode* node = doc.RootElement()->Clone();
    EXPECT_EQ(expected,
              XMLUtils::NodeStringSerialization(node, XMLUtils::SerializationFormat::COMPACT));
    // the node is still functional after serialization
    EXPECT_NE(nullptr, node->FirstChildElement("node"));
    // Free allocated memory
    TiXmlDocument tempdoc;
    tempdoc.LinkEndChild(node);
  }
  {
    // TinyXML2 doesn't allow freestanding XMLNodes. They are always memory-managed by a XMLDocument.
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, NodeSerializationChild)
{
  const std::string XmlDocument = "<root><node>some string</node></root>";
  const std::string expected = "<node>some string</node>";

  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    TiXmlElement* elem = doc.RootElement()->FirstChildElement("node");
    EXPECT_EQ(expected,
              XMLUtils::NodeStringSerialization(elem, XMLUtils::SerializationFormat::COMPACT));
  }
  {
    // TinyXML2 doesn't allow freestanding XMLNodes. They are always memory-managed by a XMLDocument.
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    tinyxml2::XMLElement* elem = doc.RootElement()->FirstChildElement("node");

    EXPECT_EQ(expected,
              XMLUtils::NodeStringSerialization(elem, XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, NodeSerializationCompact)
{
  const std::string XmlDocument = "<root><node>some string</node></root>";
  const std::string expected = "<root><node>some string</node></root>";

  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, NodeSerializationPretty)
{
  const std::string XmlDocument = "<root><node>some string</node></root>";
  const std::string expected = R"(<root>
    <node>some string</node>
</root>
)";

  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::PRETTY));
  }
  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::PRETTY));
  }
}

TEST(TestXMLUtils, RemoveNodeFastFail)
{
  const std::string XmlDocument = "<root><node>some string</node></root>";
  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));

    // the root element can't be deleted
    EXPECT_FALSE(XMLUtils::RemoveNode(doc.RootElement()));

    EXPECT_FALSE(XMLUtils::RemoveNode(static_cast<TiXmlElement*>(nullptr)));
  }

  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));

    // the root element can't be deleted
    EXPECT_FALSE(XMLUtils::RemoveNode(doc.RootElement()));

    EXPECT_FALSE(XMLUtils::RemoveNode(static_cast<tinyxml2::XMLElement*>(nullptr)));
  }
}

TEST(TestXMLUtils, RemoveNode)
{
  const std::string XmlDocument = "<root><node>some string</node><other>string</other></root>";
  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    TiXmlNode* node = doc.RootElement()->FirstChildElement("node");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }

  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    tinyxml2::XMLNode* root = doc.RootElement();
    tinyxml2::XMLNode* node = root->FirstChildElement("node");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, RemoveNodeWithChild)
{
  const std::string XmlDocument =
      "<root><node><child>some string</child></node><other>string</other></root>";
  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    TiXmlNode* node = doc.RootElement()->FirstChildElement("node");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }

  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    tinyxml2::XMLNode* root = doc.RootElement();
    tinyxml2::XMLNode* node = root->FirstChildElement("node");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, RemoveChildNode)
{
  const std::string XmlDocument =
      "<root><node>node string<child>some string</child></node><other>string</other></root>";
  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    TiXmlNode* node = doc.RootElement()->FirstChildElement("node");
    node = node->FirstChildElement("child");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><node>node string</node><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    tinyxml2::XMLNode* root = doc.RootElement();
    tinyxml2::XMLNode* node = root->FirstChildElement("node");
    node = node->FirstChildElement("child");

    EXPECT_TRUE(XMLUtils::RemoveNode(node));
    std::string expected = "<root><node>node string</node><other>string</other></root>";

    EXPECT_EQ(expected, XMLUtils::NodeStringSerialization(doc.RootElement(),
                                                          XMLUtils::SerializationFormat::COMPACT));
  }
}

TEST(TestXMLUtils, RemoveNodeFreestanding)
{
  const std::string XmlDocument = "<root><node>some string</node><other>string</other></root>";
  {
    CTinyXML doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    TiXmlNode* node = doc.RootElement()->FirstChildElement("node");

    TiXmlNode* clone = node->Clone();

    EXPECT_FALSE(XMLUtils::RemoveNode(clone));

    TiXmlDocument tempdoc;
    tempdoc.LinkEndChild(clone);
  }

  {
    CTinyXML2 doc;
    EXPECT_TRUE(doc.Parse(XmlDocument));
    tinyxml2::XMLNode* root = doc.RootElement();
    tinyxml2::XMLNode* node = root->FirstChildElement("node");

    tinyxml2::XMLNode* clone = node->DeepClone(nullptr);

    EXPECT_FALSE(XMLUtils::RemoveNode(clone));
  }
}
