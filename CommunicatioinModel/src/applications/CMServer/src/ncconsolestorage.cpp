#include "ncconsolestorage.hpp"
namespace ncconsole {
using namespace litesql;
DeviceDeviceGroupRelationDevGroup::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : deviceGroup(DeviceDeviceGroupRelationDevGroup::DeviceGroup), device(DeviceDeviceGroupRelationDevGroup::Device) {
    switch(rec.size()) {
    case 2:
        deviceGroup = rec[1];
    case 1:
        device = rec[0];
    }
}
const std::string DeviceDeviceGroupRelationDevGroup::table__("Device_DeviceGroup_DevGroup");
const litesql::FieldType DeviceDeviceGroupRelationDevGroup::Device("Device1",A_field_type_integer,table__);
const litesql::FieldType DeviceDeviceGroupRelationDevGroup::DeviceGroup("DeviceGroup2",A_field_type_integer,table__);
void DeviceDeviceGroupRelationDevGroup::link(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::DeviceGroup& o1) {
    Record values;
    Split fields;
    fields.push_back(Device.name());
    values.push_back(o0.id);
    fields.push_back(DeviceGroup.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void DeviceDeviceGroupRelationDevGroup::unlink(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::DeviceGroup& o1) {
    db.delete_(table__, (Device == o0.id && DeviceGroup == o1.id));
}
void DeviceDeviceGroupRelationDevGroup::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> DeviceDeviceGroupRelationDevGroup::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Device.fullName());
    sel.result(DeviceGroup.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<DeviceDeviceGroupRelationDevGroup::Row>(db, sel);
}
template <> litesql::DataSource<ncconsole::Device> DeviceDeviceGroupRelationDevGroup::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Device.fullName());
    sel.where(srcExpr);
    return DataSource<ncconsole::Device>(db, ncconsole::Device::Id.in(sel) && expr);
}
template <> litesql::DataSource<ncconsole::DeviceGroup> DeviceDeviceGroupRelationDevGroup::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(DeviceGroup.fullName());
    sel.where(srcExpr);
    return DataSource<ncconsole::DeviceGroup>(db, ncconsole::DeviceGroup::Id.in(sel) && expr);
}
DeviceSubnetRelationDevSubnet::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : subnet(DeviceSubnetRelationDevSubnet::Subnet), device(DeviceSubnetRelationDevSubnet::Device) {
    switch(rec.size()) {
    case 2:
        subnet = rec[1];
    case 1:
        device = rec[0];
    }
}
const std::string DeviceSubnetRelationDevSubnet::table__("Device_Subnet_DevSubnet");
const litesql::FieldType DeviceSubnetRelationDevSubnet::Device("Device1",A_field_type_integer,table__);
const litesql::FieldType DeviceSubnetRelationDevSubnet::Subnet("Subnet2",A_field_type_integer,table__);
void DeviceSubnetRelationDevSubnet::link(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::Subnet& o1) {
    Record values;
    Split fields;
    fields.push_back(Device.name());
    values.push_back(o0.id);
    fields.push_back(Subnet.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void DeviceSubnetRelationDevSubnet::unlink(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::Subnet& o1) {
    db.delete_(table__, (Device == o0.id && Subnet == o1.id));
}
void DeviceSubnetRelationDevSubnet::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> DeviceSubnetRelationDevSubnet::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Device.fullName());
    sel.result(Subnet.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<DeviceSubnetRelationDevSubnet::Row>(db, sel);
}
template <> litesql::DataSource<ncconsole::Device> DeviceSubnetRelationDevSubnet::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Device.fullName());
    sel.where(srcExpr);
    return DataSource<ncconsole::Device>(db, ncconsole::Device::Id.in(sel) && expr);
}
template <> litesql::DataSource<ncconsole::Subnet> DeviceSubnetRelationDevSubnet::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Subnet.fullName());
    sel.where(srcExpr);
    return DataSource<ncconsole::Subnet>(db, ncconsole::Subnet::Id.in(sel) && expr);
}
const litesql::FieldType Credential::Own::Id("id",A_field_type_integer,"Credential");
const std::string Credential::type__("Credential");
const std::string Credential::table__("Credential");
const std::string Credential::sequence__("Credential_seq");
const litesql::FieldType Credential::Id("id",A_field_type_integer,table__);
const litesql::FieldType Credential::Type("type",A_field_type_string,table__);
const litesql::FieldType Credential::Authname("authname",A_field_type_string,table__);
const litesql::FieldType Credential::Username("username",A_field_type_string,table__);
void Credential::initValues() {
}
void Credential::defaults() {
    id = 0;
}
Credential::Credential(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), authname(Authname), username(Username) {
    defaults();
}
Credential::Credential(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), authname(Authname), username(Username) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: username = convert<const std::string&, std::string>(rec[3]);
        username.setModified(false);
    case 3: authname = convert<const std::string&, std::string>(rec[2]);
        authname.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Credential::Credential(const Credential& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), authname(obj.authname), username(obj.username) {
}
const Credential& Credential::operator=(const Credential& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        authname = obj.authname;
        username = obj.username;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Credential::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(authname.name());
    values.push_back(authname);
    authname.setModified(false);
    fields.push_back(username.name());
    values.push_back(username);
    username.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Credential::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Credential::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, authname);
    updateField(updates, table__, username);
}
void Credential::addIDUpdates(Updates& updates) {
}
void Credential::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Authname);
    ftypes.push_back(Username);
}
void Credential::delRecord() {
    deleteFromTable(table__, id);
}
void Credential::delRelations() {
}
void Credential::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Credential::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Credential> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Credential::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Credential> Credential::upcast() const {
    return unique_ptr<Credential>(new Credential(*this));
}
std::unique_ptr<Credential> Credential::upcastCopy() const {
    Credential* np = new Credential(*this);
    np->id = id;
    np->type = type;
    np->authname = authname;
    np->username = username;
    np->inDatabase = inDatabase;
    return unique_ptr<Credential>(np);
}
std::ostream & operator<<(std::ostream& os, Credential o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.authname.name() << " = " << o.authname << std::endl;
    os << o.username.name() << " = " << o.username << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Device::Own::Id("id",A_field_type_integer,"Device");
Device::GroupsHandle::GroupsHandle(const Device& owner)
         : litesql::RelationHandle<Device>(owner) {
}
void Device::GroupsHandle::link(const DeviceGroup& o0) {
    DeviceDeviceGroupRelationDevGroup::link(owner->getDatabase(), *owner, o0);
}
void Device::GroupsHandle::unlink(const DeviceGroup& o0) {
    DeviceDeviceGroupRelationDevGroup::unlink(owner->getDatabase(), *owner, o0);
}
void Device::GroupsHandle::del(const litesql::Expr& expr) {
    DeviceDeviceGroupRelationDevGroup::del(owner->getDatabase(), expr && DeviceDeviceGroupRelationDevGroup::Device == owner->id);
}
litesql::DataSource<DeviceGroup> Device::GroupsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return DeviceDeviceGroupRelationDevGroup::get<DeviceGroup>(owner->getDatabase(), expr, (DeviceDeviceGroupRelationDevGroup::Device == owner->id) && srcExpr);
}
litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> Device::GroupsHandle::getRows(const litesql::Expr& expr) {
    return DeviceDeviceGroupRelationDevGroup::getRows(owner->getDatabase(), expr && (DeviceDeviceGroupRelationDevGroup::Device == owner->id));
}
Device::SubnetHandle::SubnetHandle(const Device& owner)
         : litesql::RelationHandle<Device>(owner) {
}
void Device::SubnetHandle::link(const Subnet& o0) {
    DeviceSubnetRelationDevSubnet::link(owner->getDatabase(), *owner, o0);
}
void Device::SubnetHandle::unlink(const Subnet& o0) {
    DeviceSubnetRelationDevSubnet::unlink(owner->getDatabase(), *owner, o0);
}
void Device::SubnetHandle::del(const litesql::Expr& expr) {
    DeviceSubnetRelationDevSubnet::del(owner->getDatabase(), expr && DeviceSubnetRelationDevSubnet::Device == owner->id);
}
litesql::DataSource<Subnet> Device::SubnetHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return DeviceSubnetRelationDevSubnet::get<Subnet>(owner->getDatabase(), expr, (DeviceSubnetRelationDevSubnet::Device == owner->id) && srcExpr);
}
litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> Device::SubnetHandle::getRows(const litesql::Expr& expr) {
    return DeviceSubnetRelationDevSubnet::getRows(owner->getDatabase(), expr && (DeviceSubnetRelationDevSubnet::Device == owner->id));
}
const std::string Device::type__("Device");
const std::string Device::table__("Device");
const std::string Device::sequence__("Device_seq");
const litesql::FieldType Device::Id("id",A_field_type_integer,table__);
const litesql::FieldType Device::Type("type",A_field_type_string,table__);
const litesql::FieldType Device::Uniquename("uniquename",A_field_type_string,table__);
const litesql::FieldType Device::Name("name",A_field_type_string,table__);
void Device::initValues() {
}
void Device::defaults() {
    id = 0;
}
Device::Device(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
}
Device::Device(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: uniquename = convert<const std::string&, std::string>(rec[2]);
        uniquename.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Device::Device(const Device& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), uniquename(obj.uniquename), name(obj.name) {
}
const Device& Device::operator=(const Device& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        uniquename = obj.uniquename;
        name = obj.name;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Device::GroupsHandle Device::groups() {
    return Device::GroupsHandle(*this);
}
Device::SubnetHandle Device::subnet() {
    return Device::SubnetHandle(*this);
}
std::string Device::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(uniquename.name());
    values.push_back(uniquename);
    uniquename.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Device::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Device::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, uniquename);
    updateField(updates, table__, name);
}
void Device::addIDUpdates(Updates& updates) {
}
void Device::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Uniquename);
    ftypes.push_back(Name);
}
void Device::delRecord() {
    deleteFromTable(table__, id);
}
void Device::delRelations() {
    DeviceDeviceGroupRelationDevGroup::del(*db, (DeviceDeviceGroupRelationDevGroup::Device == id));
    DeviceSubnetRelationDevSubnet::del(*db, (DeviceSubnetRelationDevSubnet::Device == id));
}
void Device::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Device::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Device> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Device::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Device> Device::upcast() const {
    return unique_ptr<Device>(new Device(*this));
}
std::unique_ptr<Device> Device::upcastCopy() const {
    Device* np = new Device(*this);
    np->id = id;
    np->type = type;
    np->uniquename = uniquename;
    np->name = name;
    np->inDatabase = inDatabase;
    return unique_ptr<Device>(np);
}
std::ostream & operator<<(std::ostream& os, Device o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.uniquename.name() << " = " << o.uniquename << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType DeviceGroup::Own::Id("id",A_field_type_integer,"DeviceGroup");
DeviceGroup::DevicesHandle::DevicesHandle(const DeviceGroup& owner)
         : litesql::RelationHandle<DeviceGroup>(owner) {
}
void DeviceGroup::DevicesHandle::link(const Device& o0) {
    DeviceDeviceGroupRelationDevGroup::link(owner->getDatabase(), o0, *owner);
}
void DeviceGroup::DevicesHandle::unlink(const Device& o0) {
    DeviceDeviceGroupRelationDevGroup::unlink(owner->getDatabase(), o0, *owner);
}
void DeviceGroup::DevicesHandle::del(const litesql::Expr& expr) {
    DeviceDeviceGroupRelationDevGroup::del(owner->getDatabase(), expr && DeviceDeviceGroupRelationDevGroup::DeviceGroup == owner->id);
}
litesql::DataSource<Device> DeviceGroup::DevicesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return DeviceDeviceGroupRelationDevGroup::get<Device>(owner->getDatabase(), expr, (DeviceDeviceGroupRelationDevGroup::DeviceGroup == owner->id) && srcExpr);
}
litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> DeviceGroup::DevicesHandle::getRows(const litesql::Expr& expr) {
    return DeviceDeviceGroupRelationDevGroup::getRows(owner->getDatabase(), expr && (DeviceDeviceGroupRelationDevGroup::DeviceGroup == owner->id));
}
const std::string DeviceGroup::type__("DeviceGroup");
const std::string DeviceGroup::table__("DeviceGroup");
const std::string DeviceGroup::sequence__("DeviceGroup_seq");
const litesql::FieldType DeviceGroup::Id("id",A_field_type_integer,table__);
const litesql::FieldType DeviceGroup::Type("type",A_field_type_string,table__);
const litesql::FieldType DeviceGroup::Uniquename("uniquename",A_field_type_string,table__);
const litesql::FieldType DeviceGroup::Name("name",A_field_type_string,table__);
void DeviceGroup::initValues() {
}
void DeviceGroup::defaults() {
    id = 0;
}
DeviceGroup::DeviceGroup(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
}
DeviceGroup::DeviceGroup(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: uniquename = convert<const std::string&, std::string>(rec[2]);
        uniquename.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
DeviceGroup::DeviceGroup(const DeviceGroup& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), uniquename(obj.uniquename), name(obj.name) {
}
const DeviceGroup& DeviceGroup::operator=(const DeviceGroup& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        uniquename = obj.uniquename;
        name = obj.name;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
DeviceGroup::DevicesHandle DeviceGroup::devices() {
    return DeviceGroup::DevicesHandle(*this);
}
std::string DeviceGroup::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(uniquename.name());
    values.push_back(uniquename);
    uniquename.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void DeviceGroup::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void DeviceGroup::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, uniquename);
    updateField(updates, table__, name);
}
void DeviceGroup::addIDUpdates(Updates& updates) {
}
void DeviceGroup::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Uniquename);
    ftypes.push_back(Name);
}
void DeviceGroup::delRecord() {
    deleteFromTable(table__, id);
}
void DeviceGroup::delRelations() {
    DeviceDeviceGroupRelationDevGroup::del(*db, (DeviceDeviceGroupRelationDevGroup::DeviceGroup == id));
}
void DeviceGroup::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void DeviceGroup::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<DeviceGroup> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool DeviceGroup::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<DeviceGroup> DeviceGroup::upcast() const {
    return unique_ptr<DeviceGroup>(new DeviceGroup(*this));
}
std::unique_ptr<DeviceGroup> DeviceGroup::upcastCopy() const {
    DeviceGroup* np = new DeviceGroup(*this);
    np->id = id;
    np->type = type;
    np->uniquename = uniquename;
    np->name = name;
    np->inDatabase = inDatabase;
    return unique_ptr<DeviceGroup>(np);
}
std::ostream & operator<<(std::ostream& os, DeviceGroup o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.uniquename.name() << " = " << o.uniquename << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Profile::Own::Id("id",A_field_type_integer,"Profile");
const std::string Profile::type__("Profile");
const std::string Profile::table__("Profile");
const std::string Profile::sequence__("Profile_seq");
const litesql::FieldType Profile::Id("id",A_field_type_integer,table__);
const litesql::FieldType Profile::Type("type",A_field_type_string,table__);
const litesql::FieldType Profile::Uniquename("uniquename",A_field_type_string,table__);
const litesql::FieldType Profile::Name("name",A_field_type_string,table__);
const litesql::FieldType Profile::IdScreenResolution("idScreenResolution",A_field_type_integer,table__);
void Profile::initValues() {
}
void Profile::defaults() {
    id = 0;
    idScreenResolution = 0;
}
Profile::Profile(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), uniquename(Uniquename), name(Name), idScreenResolution(IdScreenResolution) {
    defaults();
}
Profile::Profile(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), uniquename(Uniquename), name(Name), idScreenResolution(IdScreenResolution) {
    defaults();
    size_t size = (rec.size() > 5) ? 5 : rec.size();
    switch(size) {
    case 5: idScreenResolution = convert<const std::string&, int>(rec[4]);
        idScreenResolution.setModified(false);
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: uniquename = convert<const std::string&, std::string>(rec[2]);
        uniquename.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Profile::Profile(const Profile& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), uniquename(obj.uniquename), name(obj.name), idScreenResolution(obj.idScreenResolution) {
}
const Profile& Profile::operator=(const Profile& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        uniquename = obj.uniquename;
        name = obj.name;
        idScreenResolution = obj.idScreenResolution;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Profile::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(uniquename.name());
    values.push_back(uniquename);
    uniquename.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(idScreenResolution.name());
    values.push_back(idScreenResolution);
    idScreenResolution.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Profile::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Profile::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, uniquename);
    updateField(updates, table__, name);
    updateField(updates, table__, idScreenResolution);
}
void Profile::addIDUpdates(Updates& updates) {
}
void Profile::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Uniquename);
    ftypes.push_back(Name);
    ftypes.push_back(IdScreenResolution);
}
void Profile::delRecord() {
    deleteFromTable(table__, id);
}
void Profile::delRelations() {
}
void Profile::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Profile::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Profile> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Profile::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Profile> Profile::upcast() const {
    return unique_ptr<Profile>(new Profile(*this));
}
std::unique_ptr<Profile> Profile::upcastCopy() const {
    Profile* np = new Profile(*this);
    np->id = id;
    np->type = type;
    np->uniquename = uniquename;
    np->name = name;
    np->idScreenResolution = idScreenResolution;
    np->inDatabase = inDatabase;
    return unique_ptr<Profile>(np);
}
std::ostream & operator<<(std::ostream& os, Profile o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.uniquename.name() << " = " << o.uniquename << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.idScreenResolution.name() << " = " << o.idScreenResolution << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Subnet::Own::Id("id",A_field_type_integer,"Subnet");
Subnet::DeviceHandle::DeviceHandle(const Subnet& owner)
         : litesql::RelationHandle<Subnet>(owner) {
}
void Subnet::DeviceHandle::link(const Device& o0) {
    DeviceSubnetRelationDevSubnet::link(owner->getDatabase(), o0, *owner);
}
void Subnet::DeviceHandle::unlink(const Device& o0) {
    DeviceSubnetRelationDevSubnet::unlink(owner->getDatabase(), o0, *owner);
}
void Subnet::DeviceHandle::del(const litesql::Expr& expr) {
    DeviceSubnetRelationDevSubnet::del(owner->getDatabase(), expr && DeviceSubnetRelationDevSubnet::Subnet == owner->id);
}
litesql::DataSource<Device> Subnet::DeviceHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return DeviceSubnetRelationDevSubnet::get<Device>(owner->getDatabase(), expr, (DeviceSubnetRelationDevSubnet::Subnet == owner->id) && srcExpr);
}
litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> Subnet::DeviceHandle::getRows(const litesql::Expr& expr) {
    return DeviceSubnetRelationDevSubnet::getRows(owner->getDatabase(), expr && (DeviceSubnetRelationDevSubnet::Subnet == owner->id));
}
const std::string Subnet::type__("Subnet");
const std::string Subnet::table__("Subnet");
const std::string Subnet::sequence__("Subnet_seq");
const litesql::FieldType Subnet::Id("id",A_field_type_integer,table__);
const litesql::FieldType Subnet::Type("type",A_field_type_string,table__);
const litesql::FieldType Subnet::Uniquename("uniquename",A_field_type_string,table__);
const litesql::FieldType Subnet::Name("name",A_field_type_string,table__);
void Subnet::initValues() {
}
void Subnet::defaults() {
    id = 0;
}
Subnet::Subnet(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
}
Subnet::Subnet(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), uniquename(Uniquename), name(Name) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: uniquename = convert<const std::string&, std::string>(rec[2]);
        uniquename.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Subnet::Subnet(const Subnet& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), uniquename(obj.uniquename), name(obj.name) {
}
const Subnet& Subnet::operator=(const Subnet& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        uniquename = obj.uniquename;
        name = obj.name;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Subnet::DeviceHandle Subnet::device() {
    return Subnet::DeviceHandle(*this);
}
std::string Subnet::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(uniquename.name());
    values.push_back(uniquename);
    uniquename.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Subnet::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Subnet::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, uniquename);
    updateField(updates, table__, name);
}
void Subnet::addIDUpdates(Updates& updates) {
}
void Subnet::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Uniquename);
    ftypes.push_back(Name);
}
void Subnet::delRecord() {
    deleteFromTable(table__, id);
}
void Subnet::delRelations() {
    DeviceSubnetRelationDevSubnet::del(*db, (DeviceSubnetRelationDevSubnet::Subnet == id));
}
void Subnet::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Subnet::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Subnet> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Subnet::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Subnet> Subnet::upcast() const {
    return unique_ptr<Subnet>(new Subnet(*this));
}
std::unique_ptr<Subnet> Subnet::upcastCopy() const {
    Subnet* np = new Subnet(*this);
    np->id = id;
    np->type = type;
    np->uniquename = uniquename;
    np->name = name;
    np->inDatabase = inDatabase;
    return unique_ptr<Subnet>(np);
}
std::ostream & operator<<(std::ostream& os, Subnet o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.uniquename.name() << " = " << o.uniquename << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
NCConsoleStorage::NCConsoleStorage(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> NCConsoleStorage::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("Credential_seq","sequence",backend->getCreateSequenceSQL("Credential_seq")));
        res.push_back(Database::SchemaItem("Device_seq","sequence",backend->getCreateSequenceSQL("Device_seq")));
        res.push_back(Database::SchemaItem("DeviceGroup_seq","sequence",backend->getCreateSequenceSQL("DeviceGroup_seq")));
        res.push_back(Database::SchemaItem("Profile_seq","sequence",backend->getCreateSequenceSQL("Profile_seq")));
        res.push_back(Database::SchemaItem("Subnet_seq","sequence",backend->getCreateSequenceSQL("Subnet_seq")));
    }
    res.push_back(Database::SchemaItem("Credential","table","CREATE TABLE Credential (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",authname " + backend->getSQLType(A_field_type_string,"") + "" +",username " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Device","table","CREATE TABLE Device (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",uniquename " + backend->getSQLType(A_field_type_string,"") + " UNIQUE" +",name " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("DeviceGroup","table","CREATE TABLE DeviceGroup (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",uniquename " + backend->getSQLType(A_field_type_string,"") + " UNIQUE" +",name " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Profile","table","CREATE TABLE Profile (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",uniquename " + backend->getSQLType(A_field_type_string,"") + " UNIQUE" +",name " + backend->getSQLType(A_field_type_string,"") + "" +",idScreenResolution " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Subnet","table","CREATE TABLE Subnet (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",uniquename " + backend->getSQLType(A_field_type_string,"") + " UNIQUE" +",name " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Device_DeviceGroup_DevGroup","table","CREATE TABLE Device_DeviceGroup_DevGroup (Device1 " + backend->getSQLType(A_field_type_integer,"") + "" +",DeviceGroup2 " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Device_Subnet_DevSubnet","table","CREATE TABLE Device_Subnet_DevSubnet (Device1 " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +",Subnet2 " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("Credentialididx","index","CREATE INDEX Credentialididx ON Credential (id)"));
    res.push_back(Database::SchemaItem("Deviceididx","index","CREATE INDEX Deviceididx ON Device (id)"));
    res.push_back(Database::SchemaItem("DeviceGroupididx","index","CREATE INDEX DeviceGroupididx ON DeviceGroup (id)"));
    res.push_back(Database::SchemaItem("Profileididx","index","CREATE INDEX Profileididx ON Profile (id)"));
    res.push_back(Database::SchemaItem("Subnetididx","index","CREATE INDEX Subnetididx ON Subnet (id)"));
    res.push_back(Database::SchemaItem("O23ee92957fe29c6079b1745521b1e","index","CREATE INDEX O23ee92957fe29c6079b1745521b1e ON Device_DeviceGroup_DevGroup (Device1)"));
    res.push_back(Database::SchemaItem("O893312c935787c485ae925c626cba","index","CREATE INDEX O893312c935787c485ae925c626cba ON Device_DeviceGroup_DevGroup (DeviceGroup2)"));
    res.push_back(Database::SchemaItem("O9798c2e3c1a85a2d73f22781748a8","index","CREATE INDEX O9798c2e3c1a85a2d73f22781748a8 ON Device_DeviceGroup_DevGroup (Device1,DeviceGroup2)"));
    res.push_back(Database::SchemaItem("O9b4a8421928863fbb0c78d0e220d3","index","CREATE INDEX O9b4a8421928863fbb0c78d0e220d3 ON Device_Subnet_DevSubnet (Device1)"));
    res.push_back(Database::SchemaItem("Of38a032e322cc55f8dab5e420a1d3","index","CREATE INDEX Of38a032e322cc55f8dab5e420a1d3 ON Device_Subnet_DevSubnet (Subnet2)"));
    res.push_back(Database::SchemaItem("O94d961e4d063be0eb0cae5600e5d0","index","CREATE INDEX O94d961e4d063be0eb0cae5600e5d0 ON Device_Subnet_DevSubnet (Device1,Subnet2)"));
    return res;
}
void NCConsoleStorage::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
