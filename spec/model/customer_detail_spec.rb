require 'rails_helper'

RSpec.describe CustomerDetail, type: :model do
    subject { CustomerDetail.new(name: 'ved' ,car_color: 'black' ,car_number: 'MP09HP2022', in_time: '29/12/2022 11:36', out_time: '29/12/2022 11:36', slot_id: 1, confirm: 'confirm',
        user_id: 1) } 
    before {subject.save}

    it 'Name Should Be Present' do
        subject.name = nil
        expect(subject).to_not be_valid
    end

    it 'Car Color Should Be Present' do 
        subject.car_color = nil
        expect(subject).to_not be_valid
    end

    it 'Car Number Sould Be Present' do 
        subject.car_number = nil
        expect(subject).to_not be_valid
    end
     
    it 'In Time Should Be Present' do
        subject.in_time = nil
        expect(subject).to_not be_valid
    end

    it 'Out Time Should Be Present' do 
        subject.out_time = nil
        expect(subject).to_not be_valid
    end

    it 'Slot Id Should Be Present' do
        subject.slot_id = nil
        expect(subject).to_not be_valid
    end

    it 'User Id Should Be Present' do
        subject.user_id = nil
        expect(subject).to_not be_valid
    end

    it 'Name Should Not Be To Long' do
        subject.name = 'a' * 30
        expect(subject).to_not be_valid
    end

    it 'Car Color Should Not Be Too Long' do
        subject.car_color = 'a' * 30
        expect(subject).to_not be_valid
    end

    it 'In Time Should Not Be Before the Curent Date And Time ' do
        subject.in_time = 1.day.ago
        expect(subject).to_not be_valid
    end

        
end