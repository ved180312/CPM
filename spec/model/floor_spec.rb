require 'rails_helper'

RSpec.describe Floor, type: :model do
    subject { Floor.new(number_of_floor: 1)}
    before {subject.save}

    it 'Numbar Of Floor Should Be Present' do
        subject.number_of_floor = nil
        expect(subject).to_not be_valid
    end 

    it 'Numbar Of Floor Should Allow Vaild Value' do
        subject.number_of_floor = nil
        expect(subject).to_not be_valid
    end
end