#ifndef ncconsolestorage_hpp
#define ncconsolestorage_hpp
#include "litesql.hpp"
namespace ncconsole {
class Credential;
class Device;
class DeviceGroup;
class Profile;
class Subnet;
class DeviceDeviceGroupRelationDevGroup {
public:
    class Row {
    public:
        litesql::Field<int> deviceGroup;
        litesql::Field<int> device;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Device;
    static const litesql::FieldType DeviceGroup;
    static void link(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::DeviceGroup& o1);
    static void unlink(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::DeviceGroup& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class DeviceSubnetRelationDevSubnet {
public:
    class Row {
    public:
        litesql::Field<int> subnet;
        litesql::Field<int> device;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Device;
    static const litesql::FieldType Subnet;
    static void link(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::Subnet& o1);
    static void unlink(const litesql::Database& db, const ncconsole::Device& o0, const ncconsole::Subnet& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class Credential : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Authname;
    litesql::Field<std::string> authname;
    static const litesql::FieldType Username;
    litesql::Field<std::string> username;
    static void initValues();
protected:
    void defaults();
public:
    Credential(const litesql::Database& db);
    Credential(const litesql::Database& db, const litesql::Record& rec);
    Credential(const Credential& obj);
    const Credential& operator=(const Credential& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Credential> upcast() const;
    std::unique_ptr<Credential> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Credential o);
class Device : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class GroupsHandle : public litesql::RelationHandle<Device> {
    public:
        GroupsHandle(const Device& owner);
        void link(const DeviceGroup& o0);
        void unlink(const DeviceGroup& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<DeviceGroup> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class SubnetHandle : public litesql::RelationHandle<Device> {
    public:
        SubnetHandle(const Device& owner);
        void link(const Subnet& o0);
        void unlink(const Subnet& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Subnet> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Uniquename;
    litesql::Field<std::string> uniquename;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static void initValues();
protected:
    void defaults();
public:
    Device(const litesql::Database& db);
    Device(const litesql::Database& db, const litesql::Record& rec);
    Device(const Device& obj);
    const Device& operator=(const Device& obj);
    Device::GroupsHandle groups();
    Device::SubnetHandle subnet();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Device> upcast() const;
    std::unique_ptr<Device> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Device o);
class DeviceGroup : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class DevicesHandle : public litesql::RelationHandle<DeviceGroup> {
    public:
        DevicesHandle(const DeviceGroup& owner);
        void link(const Device& o0);
        void unlink(const Device& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Device> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<DeviceDeviceGroupRelationDevGroup::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Uniquename;
    litesql::Field<std::string> uniquename;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static void initValues();
protected:
    void defaults();
public:
    DeviceGroup(const litesql::Database& db);
    DeviceGroup(const litesql::Database& db, const litesql::Record& rec);
    DeviceGroup(const DeviceGroup& obj);
    const DeviceGroup& operator=(const DeviceGroup& obj);
    DeviceGroup::DevicesHandle devices();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<DeviceGroup> upcast() const;
    std::unique_ptr<DeviceGroup> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, DeviceGroup o);
class Profile : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Uniquename;
    litesql::Field<std::string> uniquename;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static void initValues();
protected:
    void defaults();
public:
    Profile(const litesql::Database& db);
    Profile(const litesql::Database& db, const litesql::Record& rec);
    Profile(const Profile& obj);
    const Profile& operator=(const Profile& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Profile> upcast() const;
    std::unique_ptr<Profile> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Profile o);
class Subnet : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class DeviceHandle : public litesql::RelationHandle<Subnet> {
    public:
        DeviceHandle(const Subnet& owner);
        void link(const Device& o0);
        void unlink(const Device& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Device> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<DeviceSubnetRelationDevSubnet::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Uniquename;
    litesql::Field<std::string> uniquename;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static void initValues();
protected:
    void defaults();
public:
    Subnet(const litesql::Database& db);
    Subnet(const litesql::Database& db, const litesql::Record& rec);
    Subnet(const Subnet& obj);
    const Subnet& operator=(const Subnet& obj);
    Subnet::DeviceHandle device();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Subnet> upcast() const;
    std::unique_ptr<Subnet> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Subnet o);
class NCConsoleStorage : public litesql::Database {
public:
    NCConsoleStorage(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
