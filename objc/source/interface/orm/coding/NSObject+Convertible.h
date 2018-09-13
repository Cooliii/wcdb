/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <WCDB/WCTCommon.h>

namespace WCDB {

//NSObject
template<>
class LiteralValueConvertible<NSObject *> : public std::true_type {
public:
    static LiteralValue as(NSObject *const &t);
};

template<>
class ExpressionConvertible<NSObject *> : public std::true_type {
public:
    static Expression as(NSObject *const &t);
};

//NSObject Subclass
template<typename T, typename Enable = void>
struct IsObjCType : std::false_type {
};

template<typename T>
struct IsObjCType<
T,
typename std::enable_if<std::is_convertible<NSObject *, T>::value && std::is_pointer<T>::value>::type> : std::true_type {
};

template<typename T>
class LiteralValueConvertible<
T,
typename std::enable_if<IsObjCType<T>::value>::type>
: public std::true_type {
public:
    static LiteralValue as(const T &t);
};

//NSObject Subclass Implementation
template<typename T>
LiteralValue LiteralValueConvertible<
T,
typename std::enable_if<IsObjCType<T>::value>::type>::as(const T &t)
{
    return LiteralValueConvertible<NSObject *>::as(t);
}

//WCTProperty
template<>
class ExpressionConvertible<WCTProperty> : public std::true_type {
public:
    static Expression as(const WCTProperty &property);
};

//NSString
template<>
struct ColumnIsTextType<NSString *> : public std::true_type {
public:
    static ColumnTypeInfo<ColumnType::Text>::UnderlyingType
    asUnderlyingType(NSString *text);
};

template<>
class LiteralValueConvertible<NSString *> : public std::true_type {
public:
    static LiteralValue as(NSString *const &t);
};

template<>
class ExpressionConvertible<NSString *> : public std::true_type {
public:
    static Expression as(NSString *const &t);
};

} //namespace WCDB