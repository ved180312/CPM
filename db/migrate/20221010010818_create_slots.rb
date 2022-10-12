class CreateSlots < ActiveRecord::Migration[7.0]
  def change
    create_table :slots do |t|
      t.integer :slot_number

      t.timestamps
    end
  end
end
